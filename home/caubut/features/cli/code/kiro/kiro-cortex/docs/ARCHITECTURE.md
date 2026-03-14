# Kiro Cortex Architecture

## Problem

Steering files don't scale. As repos, agents, and policies grow, context windows fill with irrelevant instructions. 35+ files across personal + one work repo = ~31K tokens loaded every session. Most are irrelevant to the current task. The LLM forgets or misapplies rules buried in noise.

## Solution — In One Sentence

RAG over steering files, with policy governance and workflow orchestration layered on top.

All codified knowledge — steering rules, coding standards, repo conventions — gets parsed into structured rows in a PostgreSQL table (`instructions`), each tagged with metadata and an embedding vector. When a task arrives, kiro-cortex searches for semantically relevant instructions, filters by metadata, trims to a token budget, and returns only what the agent needs.

## Layered Design

The system is built in layers. Each layer adds capability on top of the previous one. Phase 3 builds the core. Later phases add policy and workflow layers.

### Layer 1: Core RAG Loop (Phase 3)

The foundation. A query comes in, relevant instructions come out.

```
                         kiro-cortex (Effect-TS server, port 3100)
                         ═══════════════════════════════════════
                                        │
  ┌─────────────────────────────────────┼──────────────────────────────────┐
  │                                     │                                  │
  │  1. Request arrives                 ▼                                  │
  │     {query, agent_role,    ┌────────────────┐                          │
  │      task_type, domain,    │  Embed query    │──→ Ollama (localhost)    │
  │      token_budget}         │  via Ollama     │←── embedding vector      │
  │                            └───────┬────────┘                          │
  │                                    │                                   │
  │  2. Search instructions            ▼                                   │
  │                            ┌────────────────┐                          │
  │                            │  PostgreSQL     │  SELECT * FROM           │
  │                            │  (kiro_cortex)  │  instructions            │
  │                            │                 │  WHERE domain = ...      │
  │                            │  pgvector HNSW  │  AND agent_roles @> ...  │
  │                            │  cosine search  │  ORDER BY embedding      │
  │                            └───────┬────────┘  <=> query_vec           │
  │                                    │           LIMIT N                  │
  │  3. Assemble context               ▼                                   │
  │                            ┌────────────────┐                          │
  │                            │  Rank by        │                          │
  │                            │  priority,      │                          │
  │                            │  trim to token  │                          │
  │                            │  budget         │                          │
  │                            └───────┬────────┘                          │
  │                                    │                                   │
  │  4. Return                         ▼                                   │
  │                            {instructions, metadata, token_count}        │
  └────────────────────────────────────────────────────────────────────────┘
```

**Who does what:**
- **kiro-cortex** manages the instructions table (CRUD, search, assembly). It is the only thing that talks to PostgreSQL.
- **Ollama** (nomic-embed-text) converts text to 768-dim vectors. Stateless. Called via HTTP on localhost:11434.
- **PostgreSQL** (kiro_cortex DB) stores instructions with metadata + embeddings. pgvector extension provides HNSW cosine search.

### Layer 2: Policy Governance (Phase 4)

OPA sits in front of the search step. Instead of hardcoded SQL WHERE clauses, OPA evaluates declarative Rego policies and returns filtering criteria.

```
  Request context                         Filtering criteria
  {agent_role, task_type,     ┌─────┐    {allowed_domains: [...],
   domain, tier}         ──→  │ OPA │──→  max_tier: 2,
                              └─────┘     excluded_groups: [...]}
                                │
                    kiro-cortex applies criteria
                    as SQL WHERE on instructions table
```

**OPA does NOT talk to PostgreSQL.** OPA is a stateless policy engine. kiro-cortex sends it request context, OPA evaluates Rego rules, returns filtering criteria. kiro-cortex translates those criteria into SQL WHERE clauses.

**OPA does NOT hold instructions.** OPA holds policies (Rego files). Instructions live in PostgreSQL.

**Why OPA instead of just SQL WHERE?**
- Declarative policies separate from application code
- Complex rules hard to express in SQL (e.g., "if agent=X AND task=Y, allow domain=Z UNLESS conflict_group=W")
- Policy versioning and testing (`opa test`)
- Audit trail of policy decisions
- Reusable across entry points

#### OPA Policy Design

**Policy file structure** (replaces `test.rego`):

```
policies/
  access.rego          # request-level allow/deny (was test.rego)
  scoping.rego         # per-block instruction filtering
  isolation.rego       # repo isolation rules
```

**access.rego** — request-level access control:
```rego
package cortex.access

# Allow any authenticated request
default allow = false
allow if { input.user_id != "" }

# Deny patterns (content filtering, rate limiting, etc.)
default deny = false
deny if { contains(lower(input.query), "forbidden") }

decision := { "allowed": allow, "denied": deny, "reason": reason }
```

**scoping.rego** — per-block instruction filtering (the core of scale):
```rego
package cortex.scoping

# Input: { agent_role, task_type, domain, repo }
# Output: SQL WHERE criteria for instruction search

# Default: return all matching domain instructions
filters := {
  "allowed_domains": allowed_domains,
  "allowed_task_types": allowed_task_types,
  "repo_filter": repo_filter,
  "max_results": max_results,
}

# Domain scoping: block only sees instructions in its domain
allowed_domains contains input.domain if { input.domain != "" }
allowed_domains contains "global" # always include global instructions

# Task type scoping: block only sees instructions for its task type
allowed_task_types contains input.task_type

# Repo isolation: repo-specific instructions only for that repo
repo_filter := input.repo if { input.repo != null }
repo_filter := null if { input.repo == null } # null = framework-agnostic only

# Result limits per block type
max_results := 50 if { input.task_type == "analysis" }
max_results := 20 if { input.task_type != "analysis" }
```

**isolation.rego** — repo boundary enforcement:
```rego
package cortex.isolation

# Prevent cross-repo instruction leakage
deny_instruction if {
  input.instruction.repo != null
  input.instruction.repo != input.request.repo
}
```

**How it connects to blocks:**

Each `BlockDef<S>` declares its OPA context:
```typescript
{
  opa: { agent_role: "workflow-builder", task_type: "authoring", domain: "meta" }
}
```

The block executor (not yet built) does:
1. Send `block.opa` context to OPA `/v1/data/cortex/scoping/filters`
2. OPA returns filtering criteria: `{ allowed_domains, allowed_task_types, repo_filter, max_results }`
3. kiro-cortex translates to SQL WHERE: `domain IN (...) AND task_type IN (...) AND (repo = ... OR repo IS NULL)`
4. pgvector search with those filters → scoped instructions for this block
5. Inject instructions into block execution context
6. Block executes with only its relevant instructions

**Migration from test.rego:**
- Rename `policies/test.rego` → `policies/access.rego`
- Update `package cortex.test` → `package cortex.access`
- Update OPA query path in `Opa.ts`: `/v1/data/cortex/test/decision` → `/v1/data/cortex/access/decision`
- Add `policies/scoping.rego` and `policies/isolation.rego`
- OPA loads all `.rego` files from `policies/` directory automatically

**Phasing:**
- Phase 3 (done): `access.rego` only (allow/deny). Instruction filtering via hardcoded SQL WHERE.
- Phase 4.4 (done): Blocks declare OPA context but don't query it yet (hardcoded logic).
- Pre-4.5 (next): Rename test.rego → access.rego. Add scoping.rego. Build block executor wrapper. Wire YAML loader.
- 4.5+: isolation.rego, complex cross-domain rules, per-repo policies.

### Layer 3: Workflow Orchestration (Phase 4)

LangGraph orchestrates multi-step workflows where each step runs the core loop with different context.

```
  ┌─ LangGraph Workflow ──────────────────────────────────────┐
  │                                                            │
  │  Step 1: Analyze                                           │
  │    OPA input: {agent=analyst, task=analyze, domain=repo}   │
  │    → core loop → instructions about analysis patterns      │
  │    → Kiro headless executes analysis                       │
  │                                                            │
  │  Step 2: Code                                              │
  │    OPA input: {agent=developer, task=code, domain=effect}  │
  │    → core loop → instructions about coding standards       │
  │    → Kiro headless writes code                             │
  │                                                            │
  │  Step 3: Review                                            │
  │    OPA input: {agent=reviewer, task=review, domain=repo}   │
  │    → core loop → instructions about review criteria        │
  │    → Kiro headless reviews the code                        │
  │                                                            │
  │  Persistent state across steps (PG checkpointer)           │
  └────────────────────────────────────────────────────────────┘
```

Each step gets DIFFERENT instructions because the OPA input is different. This is the "per-step OPA consultation" pattern — the whole point of kiro-cortex being a workflow orchestration platform, not just a context provider.

## Component Responsibilities

| Component | Manages | Talks to | Stateful? |
|-----------|---------|----------|-----------|
| **kiro-cortex** | Instructions table, context assembly, workflow orchestration | PostgreSQL, OPA, Ollama, Kiro headless | Yes (PG) |
| **PostgreSQL** | Data storage (instructions + embeddings + workflow state) | Only responds to kiro-cortex | Yes |
| **OPA** | Policy rules (Rego files) | Only responds to kiro-cortex | No (stateless) |
| **Ollama** | Embedding models | Only responds to kiro-cortex | No (stateless) |
| **Kiro headless** | Task execution with scoped context | Called by kiro-cortex | No |
| **LangGraph** | Workflow graph definition and step sequencing | Embedded in kiro-cortex | State in PG |

kiro-cortex is the **sole mediator**. No component talks directly to another. All data flows through kiro-cortex.

## Database Landscape

Two databases on the same PostgreSQL server (port 5435), different purposes:

```
  PostgreSQL (port 5435)
  ├── openmemory          ← Personal working memory (managed by OpenMemory MCP)
  │   ├── memories            Volatile, exploratory, per-user
  │   ├── vectors             89 memories, 435 vectors
  │   ├── waypoints           Managed by OpenMemory, not kiro-cortex
  │   ├── temporal_facts
  │   └── ...
  │
  └── kiro_cortex         ← Codified knowledge (managed by kiro-cortex)
      ├── instructions        Structured steering content with metadata + embeddings
      └── (future)            Workflow state, audit logs, etc.
```

**Why separate?** Different lifecycles. Memories are personal and volatile (created/deleted frequently). Instructions are shared, versioned, and stable. Different access patterns, different management, clean separation.

**OpenMemory and kiro-cortex are independent systems.** They share a PG server for convenience but have no data dependencies. kiro-cortex never reads from `openmemory`. OpenMemory never reads from `kiro_cortex`.

## Composable Workflow Blocks

### Core Principle

**Workflows ARE instructions in the DB.** Not files on disk. Skill/agent files are thin triggers — entry points that tell kiro-cli "this workflow exists." The real knowledge lives in OPA/pgvector, queryable at scale (up to 1M instructions). This replaces steering files, which cause context dilution.

**Context discipline via LangGraph.** Each step (block) in a pipeline gets ONLY its scoped instructions via OPA. This is how 1M instructions stay focused — per-step OPA consultation, not one giant prompt.

### Block Model (Lego Pieces)

Blocks are reusable, focused units. A block used in repo-analysis (e.g., `pattern-extract`) can be reused in a future `code-reviewer` workflow without duplication.

```
Block {
  id: string              // unique identifier
  name: string            // human-readable name
  inputs: Schema          // what it needs
  outputs: Schema         // what it produces
  opa_context: {          // declares what instructions this block needs
    agent_role, task_type, domain
  }
  mode: "standalone" | "pipeline" | "both"
}
```

### Pipeline Model (Wired Blocks)

LangGraph wires blocks into sequences. Each step gets tight, focused instructions — no context pollution across steps.

```
Pipeline {
  id: string
  name: string
  steps: Array<{block_id, condition?, routing?}>
  state_schema: Schema    // shared state across steps
}
```

### Execution Model

A block can be triggered via:
- **MCP tool** — from kiro-cli (MCP stdio wrapper). Returns assembled context + metadata.
- **HTTP API** — direct POST to `/blocks/{id}/run`. Can chain into pipeline steps.
- **Pipeline step** — from LangGraph orchestration. Output feeds next step's state.
- **Direct trigger** (web/Slack, future) — LangGraph routes to Kiro headless for full execution.

All share the same block implementation. Each block gets OPA-scoped instructions injected via the core RAG loop. Context size is configurable per-call via `token_budget` parameter.

### Block Reuse

When building a new workflow, the system searches existing blocks first:
1. Decompose the task into focused steps
2. Search block registry for blocks that already satisfy each step
3. Reuse existing blocks where possible
4. Create new blocks only when no existing block fits
5. Wire blocks together into a new pipeline

### Instruction Scoping

Instructions have scope enforced by OPA:
- **General framework knowledge** (e.g., Effect patterns from EffectPatterns repo): `repo: null`, `domain: "effect"` — available to any workflow needing Effect context
- **Repo-specific patterns** (e.g., "this repo uses Effect.gen exclusively"): `repo: "org/my-repo"` — only surfaces when working in that repo
- **No bleed-through** — work repo patterns never leak into personal repo context
- **Git worktree aware** — repo identified by remote origin, not directory path. Multiple worktrees for the same repo share instructions.

## Meta-Workflow (Bootstrap)

### Problem Statement

Building workflows by hand doesn't scale. Each workflow needs decomposition into focused blocks, OPA context declarations, instruction authoring, pipeline wiring, and trigger setup. Without tooling, this is error-prone and inconsistent. The meta-workflow solves this by codifying "how to build workflows" as instructions in the DB, then using those instructions to guide workflow creation — dogfooding the entire OPA/LangGraph system.

### Use Cases

- **UC-MW-1**: "Kiro, help me build a workflow to do X" → interview on goals, decompose into blocks, wire pipeline, store instructions, suggest triggers
- **UC-MW-2**: "Kiro, help me update workflow X to do Y" → find existing instructions, modify/add/deprecate, re-wire if needed
- **UC-MW-3**: "Kiro, the instructions in workflow X step Y need better instructions, here is the problem" → targeted refinement of specific step instructions
- **UC-MW-4**: A workflow (like repo-analysis) needs to generate sub-workflows as part of its output → calls meta-workflow programmatically. Short-circuits interview by providing structured input (problem statement, use cases, proposed blocks) directly to decompose. See UC-MW-12 for validation requirements.
- **UC-MW-5**: User has a vague idea but can't articulate the problem → meta-workflow helps discover and refine the problem statement through structured interview
- **UC-MW-6**: User knows the problem but not the use cases → meta-workflow helps identify concrete use cases through examples, edge cases, and "what about X?" prompts
- **UC-MW-7**: During design, meta-workflow does external research (best practices, similar systems, prior art) to inform block decomposition. Note: repo-analysis is more "one and done" post-design — its research happens at analysis time, not workflow-design time. Refine this boundary as needed.
- **UC-MW-8**: When run, meta-workflow checks if any block's instruction set has grown too large → suggests splitting the block. This is on-demand (when meta-workflow runs), not a background/cron process.
- **UC-MW-9**: Don't produce spaghetti blocks — splitting alone isn't the answer. When a split is needed, optimize the workflow holistically (reorder, merge, restructure) rather than just adding more blocks. Optimization during create/update is scoped LOCAL to the workflow being worked on — not all workflows.
- **UC-MW-10**: Keep all workflows DRY — actively look for common patterns across workflows that can be abstracted into reusable blocks configurable via inputs alone. If two workflows do similar things differently, unify them.
- **UC-MW-11**: Apply the generic historical tracking pattern to workflows whose instructions evolve over time (e.g., repo-analysis where past analysis context matters for understanding convention drift).
- **UC-MW-12**: When designing a workflow that calls meta-workflow programmatically (e.g., repo-analysis generating coding workflows), meta-workflow must ensure the calling workflow provides sufficient structured input (problem statement, use cases, proposed blocks) for the short-circuit path. Programmatic calls skip interview and go directly to decompose. If the structured input is insufficient (missing problem statement or use cases), meta-workflow should FAIL — the calling workflow wasn't designed properly.
- **UC-MW-13**: Manual audit trigger — "optimize all workflows in this repo." Standalone user-initiated entry point. Scans all workflows for instruction bloat, spaghetti, and DRY violations. Separate from per-workflow optimization during create/update.
- **UC-MW-14**: Workflows that call meta-workflow (like repo-analysis producing coding workflows) can re-optimize their FULL parent workflow scope but NOT all workflows in the repo. Meta-workflow bakes this scoped optimization into the calling workflow at design time.
- **UC-MW-15**: Git commit strategy — stacked commits are a **reusable sub-workflow**, not just a convention. Any workflow that produces file changes (meta-workflow, repo-analysis, future workflows) composes in the stacked-commit sub-workflow. It handles: stage changes → create one logical commit per change → reviewable in isolation (git-branchless/Graphite style). Meta-workflow should produce this as a reusable block/sub-workflow early, since it's needed by meta-workflow itself, repo-analysis, and any future workflow that writes files.
- **UC-MW-16**: Import/export workflows to filesystem for Nix reproducibility. Every workflow must be reconstructable from files on disk — a fresh `home-manager switch` on a new system should be able to load all workflows into a fresh DB. Meta-workflow must update these files whenever a workflow is created or updated — including when updating itself. **Decision: re-embed at load time, don't export vectors.** Vectors are derived data (deterministic given same model + text). Export only instruction text + OPA metadata + content_hash as YAML. On load, compare content_hash — only re-embed what changed. Pin nomic-embed-text model version to prevent drift. At our scale (~1K instructions), full re-embed takes ~8 seconds via local Ollama.
- **UC-MW-17**: Self-updating filesystem export — when meta-workflow updates itself (adding blocks, refining instructions), it must also update its own YAML export files in the repo so the init/seed files stay in sync with the DB state. This is the dogfooding case: meta-workflow's author/wire blocks write to DB AND export to `workflows/meta-workflow/`.
- **UC-MW-18**: Reusable sub-workflows are first-class on disk. Blocks/sub-workflows designed for cross-workflow reuse (stacked-commits, historical-tracking, etc.) live in a dedicated `shared/` directory — separate from any specific workflow. This makes reusable patterns visually distinct from workflow-specific blocks. In code, reusable blocks get their own files under `src/shared/`, not nested inside the workflow that first uses them. On the YAML export side, `workflows/shared/` holds their instructions and pipeline definitions. Any workflow can compose them in.
- _(Add more use cases here as they emerge)_

### Description

The meta-workflow is a hand-built collection of tools for the workflow lifecycle. It is the first real customer of the OPA pipeline — its instructions ("how to build workflows") are the first content in the instructions table.

**Human-in-the-loop by design.** The meta-workflow interviews the user on goals, proposes a decomposition into blocks, and iterates until the user approves. This HITL pattern must work across interfaces (kiro-cli chat now, web UI and Slack later).

### Capabilities

- **Interview**: Understand user goals — what problem the workflow solves, what triggers it, what it outputs. Help the user discover and articulate the problem statement if they have a vague idea. Help identify concrete use cases through examples, edge cases, and probing questions. Propose blocks and pipeline structure. User approves/refines.
- **Research**: Proactively discover ideas and suggest use cases the user may not have thought of. Do external research during design (best practices, similar systems, prior art) to inform decomposition. Query knowledge base for similar workflows, patterns, and best practices.
- **Build**: Decompose into blocks → find existing blocks → create new if needed → compose reusable patterns (e.g., historical tracking) → wire pipeline → store instructions in DB → suggest triggers. When building or updating, check for DRY violations across all workflows — abstract common patterns into reusable blocks configurable via inputs.
- **Update**: "Kiro, help me update workflow X to do Y" → find existing instructions → modify/add/deprecate. Check if any block's instruction set has grown too large and suggest splitting — but optimize the whole flow holistically, don't just keep adding blocks (no spaghetti).
- **Refine**: "Kiro, the instructions in workflow X step Y need better instructions" → targeted improvement of specific step instructions

### Reusable Patterns (Functional Composition)

The meta-workflow composes generic patterns into workflows. These are abstract, configurable capabilities — not workflow-specific logic. Reusable patterns are first-class on disk (UC-MW-18): they live in `src/shared/` in code and `workflows/shared/` in YAML exports, visually distinct from workflow-specific blocks.

**Historical Tracking** — for any workflow whose context drifts over time. Tracks where instructions came from and how they evolved. The specific strategy (version, migrate, deprecate, or combination) is configured per-workflow during the interview. Examples:
- repo-analysis: track convention changes so old code patterns are understood in context
- knowledge-ingest: track source versions so stale knowledge can be refreshed

**Stacked Commits** (UC-MW-15) — reusable sub-workflow for any workflow that produces file changes. Handles staging, creating one logical commit per change, reviewable in isolation. Composed into meta-workflow (author/wire/promote outputs), repo-analysis (analysis updates), and any future workflow that writes to the filesystem. This is what meta-workflow does today manually — codify it as a composable block/sub-workflow so all workflows get consistent commit discipline.

More reusable patterns will emerge as workflows are built. The meta-workflow should identify when a new workflow needs a pattern that already exists and compose it in.

### Block Breakdown

| Block | Purpose | HITL | Reusable |
|-------|---------|------|----------|
| **route** | Entry point. Classify intent (build/update/refine/audit). Load existing workflow state if update/refine. Validate structured input for programmatic calls (UC-MW-12). | No | No |
| **interview** | Multi-turn conversation via LangGraph `interrupt()`. Adapts questions based on mode. Loops with research when needed. | Yes | Potentially |
| **research** | External search for best practices, similar systems, prior art. Also searches block registry for reuse candidates. Generic — usable by any workflow. | No | Yes |
| **decompose** | Takes interview output → proposes block structure. Searches existing blocks for reuse. Applies reusable patterns (historical tracking, etc.). Calls optimize before presenting proposal. | Yes (approve/refine) | No |
| **optimize** | Reviews structure for instruction bloat (UC-MW-8), spaghetti (UC-MW-9), DRY violations (UC-MW-10). Returns recommendations — doesn't act on them. Scope: local to the workflow being worked on during create/update. Full repo scan only via manual audit trigger (UC-MW-13). | No (feeds into interview/decompose) | Yes |
| **author** | Writes/updates instructions for each block. Stores in DB with OPA metadata (agent_role, task_type, domain). | No | No |
| **wire** | Creates/updates pipeline definition (block order, conditions, routing). Stores in DB. | No | No |
| **promote** | Generates trigger artifacts (SKILL.md, agent config, MCP tool). Presents options for user to choose. | Yes | No |

### Flow Diagram

```
                              ┌───────┐
                              │ START │
                              └───┬───┘
                                  │
                              ┌───▼───┐
                              │ route │
                              └───┬───┘
                                  │
               ┌──────────┬───────┼───────────┬──────────┐
               │          │       │           │          │
           build/update  refine  audit    programmatic   │
               │          │       │       (UC-MW-4)      │
               │          │       │           │          │
               ▼          │       ▼           │     (invalid input)
          ┌─────────┐     │  ┌──────────┐    │          │
          │interview│     │  │ optimize │    │          ▼
          └────┬────┘     │  │(all wfs) │    │        FAIL
            ▲  │          │  └────┬─────┘    │    (UC-MW-12)
            │  ▼          │       │          │
          ┌──────────┐    │  ┌────▼─────┐    │
          │ research │    │  │interview │    │
          └──────────┘    │  │(findings)│    │
               │          │  └────┬─────┘    │
               ▼          │       │          │
          ┌─────────┐     │       ▼          │
          │decompose│◄────────────────────────┘
          └────┬────┘     │
            ▲  │          │
            │  ▼          │
          ┌──────────┐    │
          │ optimize │    │
          │ (local)  │    │
          └──────────┘    │
               │          │
               ▼          ▼
          ┌────────┐ ┌────────┐
          │ author │ │ author │
          └────┬───┘ └────┬───┘
               │          │
          ┌────▼──┐       ▼
          │ wire  │      END
          └────┬──┘
               │
          ┌────▼────┐
          │ promote │
          └────┬────┘
               │
              END
```

**Key loops (dynamic routing via LangGraph `Command`):**
- `interview ↔ research` — research informs interview, interview may trigger more research
- `decompose ↔ optimize` — optimize may reject, send back for restructuring
- `decompose → interview` — user may want to refine goals after seeing proposed decomposition

### Mode Paths

**BUILD** (UC-MW-1, 5, 6): route → interview ↔ research → decompose ↔ optimize → author → wire → promote → END

**UPDATE** (UC-MW-2): route (load existing) → interview ↔ research → decompose (modify) ↔ optimize → author → wire → promote → END

**REFINE** (UC-MW-3): route (load block) → interview (what's wrong) → author (rewrite) → END

**AUDIT** (UC-MW-13): route → optimize (all workflows in repo) → interview (present findings) → decompose (restructure approved items) → author → wire → promote → END

**PROGRAMMATIC** (UC-MW-4, 12): route (validate structured input) → decompose (skip interview) ↔ optimize → author → wire → promote → END. Fails if input lacks problem statement or use cases.

**SCOPED RE-OPTIMIZE** (UC-MW-14): A calling workflow (e.g., repo-analysis) triggers meta-workflow to re-optimize its full workflow scope. Scoped to the calling workflow, not all workflows. Baked into the calling workflow at design time.

### HITL Implementation

Using LangGraph `interrupt()` + PG checkpointer for pause/resume across sessions and interfaces:
- **interview**: Multi-turn `interrupt()` for each question/response cycle
- **decompose**: Single `interrupt()` presenting proposed block structure for approve/refine
- **promote**: Single `interrupt()` presenting trigger options for selection

All other blocks are autonomous. Optimize feeds recommendations into interview or decompose for human approval rather than acting independently.

### Trigger Blocks

The first block in a workflow — the entry point that kiro-cli or web UI executes. These get promoted to skills or agents so they're discoverable. The meta-workflow's end step handles this promotion.

### Why Hand-Built

The meta-workflow is the bootstrap — it can't build itself. It's the one workflow we code manually. Everything after it is produced BY it.

## Repo-Analysis (First Generated Workflow)

### Problem Statement

Developers join repos, conventions drift, and steering files go stale. Manually writing and maintaining per-repo coding standards doesn't scale across repos or over time. Repo-analysis solves this by automatically discovering patterns, conventions, and anti-patterns from the codebase itself, storing them as scoped instructions in the DB, and suggesting framework-specific knowledge sources to enhance context quality. It runs iteratively as the repo evolves, tracking convention changes so old code is understood in context.

### Use Cases

- **UC-RA-1**: First run on a new repo → discover domains, tech stack, team boundaries, extract patterns, produce repo-scoped instructions
- **UC-RA-2**: Detect Effect-TS as a major framework → suggest ingesting EffectPatterns and effect-solutions as repo-agnostic knowledge sources (HITL approval)
- **UC-RA-3**: Re-run after repo evolution → diff against previous analysis, track convention changes (e.g., "pipe chains → Effect.gen"), produce historical migration instructions. Updates to existing workflows should be straightforward and mostly automated — minimize HITL for redrafting historical workflow updates.
- **UC-RA-4**: Post-analysis → use meta-workflow to interview user on what output workflows would be useful based on findings (TBD: code-reviewer, code-assist, etc.)
- **UC-RA-5**: Multiple worktrees for same repo → share instructions, identify repo by remote origin not directory path
- **UC-RA-6**: Never add new external knowledge sources without asking. Edge case: analysis discovers best practices from a new external repo — always ask before ingesting, don't silently expand the knowledge base.
- **UC-RA-7**: When encountering ambiguous patterns or unclear conventions, ask the user rather than guessing. Uncertainty is a signal to pause, not to infer.
- _(Add more use cases here as they emerge)_

### Description

Built using the meta-workflow. Analyzes repos and produces:

1. **Instructions** — patterns, conventions, anti-patterns stored in DB (scoped to the analyzed repo)
2. **Knowledge source suggestions** — detects major frameworks and suggests repo-agnostic knowledge sources (Effect → EffectPatterns + effect-solutions, Vue → Vue docs, etc.). **Human-in-the-loop**: user approves which sources to ingest.
3. **Output workflows** — uses the meta-workflow to generate repo-specific workflows. Exact workflows TBD — the meta-workflow interviews the user on what workflows would be useful based on the analysis findings. User proposes use cases, system proposes block decompositions.

### Iterative by Design

repo-analysis runs repeatedly as the repo evolves. Uses the generic **historical tracking** pattern (configured during interview) to:
- Diff against previous analysis, detect what changed
- Track convention evolution so old code patterns are understood in context
- Maintain knowledge source ingestion state across runs

Specific historical tracking behavior (e.g., how to handle old conventions, what migration instructions to generate) is determined during the meta-workflow interview when building repo-analysis.

### Knowledge Seeding

Knowledge seeding is NOT a separate phase — it's a step within repo-analysis. When repo-analysis detects a major framework, it suggests ingesting framework-specific knowledge sources as repo-agnostic instructions. User-requested sources (EffectPatterns, effect-solutions) are tracked for ingestion post-analysis.

### Block Taxonomy (TBD — built incrementally via meta-workflow)

Initial blocks identified for repo-analysis pipeline:

| Block | Purpose |
|-------|---------|
| repo-discover | Scan repo structure, identify domains/teams/tech clusters |
| provenance-analyze | Git history heuristics for pattern authority |
| pattern-extract | Extract code patterns from a codebase |
| anti-pattern-detect | Identify anti-patterns against known good patterns |
| knowledge-suggest | Suggest framework-specific knowledge sources for ingestion |
| knowledge-ingest | Digest patterns from external repos into instructions DB |
| steering-generate | Generate instructions using 7-section framework |
| workflow-suggest | Use meta-workflow to generate repo-specific workflows |

Additional blocks and pipelines will be identified and built as needed. The meta-workflow handles creation of new blocks.

## How Instructions Get Into the Table

**Phase 3 (done):** Validated pipeline with inline psql test data (inserted and deleted).

**Phase 4b (meta-workflow bootstrap):** First real instructions = "how to build workflows." Hand-written, seeded into DB as part of building the meta-workflow.

**Phase 4c+ (repo-analysis and beyond):** All subsequent instructions produced by workflows:
```
  repo-analysis discovers patterns in a repo
    → stores repo-scoped instructions (patterns, conventions, anti-patterns)
    → suggests framework knowledge sources (e.g., EffectPatterns)
    → knowledge-ingest block parses sources → tags → embeds → inserts repo-agnostic instructions
```

**Known knowledge sources** (public, MIT-licensed, user-requested):
- [PaulJPhilp/EffectPatterns](https://github.com/PaulJPhilp/EffectPatterns) — 300+ Effect-TS patterns by category
- [kitlangton/effect-solutions](https://github.com/kitlangton/effect-solutions) — Curated Effect best practices with tested examples

Goal: up to 1,000,000 instructions across frameworks, conventions, and patterns.

## Instruction Metadata Schema

```sql
CREATE TABLE instructions (
  id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  text            TEXT NOT NULL,           -- the actual instruction content
  content_hash    VARCHAR(32),            -- MD5 of text, for incremental re-embedding (UC-MW-16)
  model_version   VARCHAR(100),           -- embedding model tag (e.g., "nomic-embed-text:v1.5")
  source          VARCHAR(255),            -- origin file path
  domain          VARCHAR(100),            -- e.g., "coding-standards", "policy", "global"
  subdomain       VARCHAR(100),            -- e.g., "effect-patterns", "ip-protection"
  repo            VARCHAR(255),            -- e.g., "org/project-a" or NULL for global
  tier_access     INTEGER[],              -- which tiers can see this [1, 2, 3]
  agent_roles     TEXT[],                 -- which roles can see this ["developer", "reviewer"]
  task_types      TEXT[],                 -- relevant for which tasks ["coding", "debugging"]
  priority        VARCHAR(20),            -- "critical", "high", "medium", "low"
  version         VARCHAR(20),
  effective_date  TIMESTAMP,
  expiry_date     TIMESTAMP,
  dependencies    UUID[],                 -- other instructions this depends on
  conflict_group  VARCHAR(100),           -- instructions that conflict with each other
  embedding       vector(768),            -- nomic-embed-text via Ollama
  created_at      TIMESTAMP DEFAULT NOW(),
  updated_at      TIMESTAMP DEFAULT NOW()
);
```

Maps to existing steering structure:
- `~/.kiro/steering/00-ip-protection.md` → domain="global", priority="critical"
- `policies/` → domain="policy", agent_roles=["all"]
- `<workspace>/.kiro/steering/` → domain=repo-specific, repo="org/repo"

## Key Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Core abstraction | RAG over steering files | Solves context dilution directly |
| Platform role | Workflow orchestration (not just context prep) | Each step needs different rules |
| Smart executor | Kiro headless (not Ollama) | Kiro has tools, reasoning, quality |
| Ollama role | Embeddings + classification only | Cheap/fast for bulk preprocessing |
| OPA in Phase 3 | Access control only (allow/deny) | SQL WHERE sufficient for filtering until policy complexity grows |
| OPA in Phase 5 | Generates filtering criteria per step | Complex policies need declarative rules |
| Single DB | PostgreSQL (metadata + vectors together) | Split via Effect Service boundary when scaling demands it |
| Vector index | HNSW over IVFFlat | Better accuracy, no training needed, works at any scale |
| Token estimation | chars/4 approximation | Upgrade to tiktoken when accuracy matters |
| Context budget | Caller-specified per request | Task complexity determines budget |
| Hosting | Self-hosted, NixOS/Home Manager | Full control, privacy, no vendor lock-in |
| Runtime | Bun + pnpm, Effect-TS | User preference, type safety |

## Phase 4a Infrastructure Detail

### Block Definition Format

Blocks are LangGraph node functions, NOT Effect.Services. Services are for infrastructure (DB, OPA, Embedding). Blocks are domain logic that uses services via Effect internally.

Each block is a TypeScript module in `src/blocks/{name}.ts` exporting a `BlockDef<S>` with metadata + an execute function. `BlockDef` is generic over the pipeline state type `S` — each pipeline defines its own state shape, and blocks are typed to their pipeline's state.

**Execution model**: Blocks are LangGraph node functions. They use Effect internally via `Effect.runPromise` for service access. No `async`/`await` — just return the Promise from `runPromise`.

```typescript
// Non-HITL block
const authorNode = (state: MetaWorkflowState) =>
  Effect.runPromise(writeInstructions(state).pipe(Effect.provide(services)))

// HITL block — interrupt() is a LangGraph primitive (throws on first call, returns value on resume)
function interviewNode(state: MetaWorkflowState) {
  const answer = interrupt({ question: "What problem does this solve?" })
  return Effect.runPromise(processAnswer(answer, state).pipe(Effect.provide(services)))
}
```

**Why LangGraph nodes, not pure Effect**: LangGraph `interrupt()` re-executes the entire node from the beginning on resume. Effect pipelines are not re-entrant. HITL blocks must call `interrupt()` directly as a LangGraph primitive, then use Effect for the work after.

### Block Metadata

```typescript
interface BlockDef<S> {
  readonly id: string
  readonly name: string
  readonly description: string
  readonly tags: ReadonlyArray<string>
  readonly opa: OpaContext               // declares what instructions this block needs
  readonly execute: (state: S) => Promise<Partial<S>>
}

interface OpaContext {
  readonly agent_role: string
  readonly task_type: string
  readonly domain: string
}
```

### Pipeline Definition Format

Pipelines wire blocks into sequences. Each pipeline defines its own state type.

```typescript
interface PipelineDef<S> {
  readonly id: string
  readonly name: string
  readonly description: string
  readonly steps: ReadonlyArray<PipelineStep>
  readonly initial_state: Partial<S>     // defaults for state fields
}

interface PipelineStep {
  readonly block_id: string
  readonly condition?: string            // when to execute (e.g., "state.mode === 'build'")
  readonly next?: string | ReadonlyArray<ConditionalNext>  // routing
}

interface ConditionalNext {
  readonly condition: string
  readonly block_id: string
}
```

### Block Registry

Explicit registration at startup. Registry is an Effect.Service (infrastructure):
- List all blocks
- Search by capability (for meta-workflow reuse check) — simple tag/name/description match for now
- Get block by ID
- In-memory Map, populated from block modules at startup

### Block Executor

The generic execution engine that runs any block:
1. Takes block's `opa` context declaration (`{ agent_role, task_type, domain }`)
2. Calls OPA scoping endpoint → gets filtering criteria (`allowed_domains`, `allowed_task_types`, `repo_filter`, `max_results`)
3. Translates OPA criteria to SQL WHERE clauses
4. Runs core RAG loop (embed query → pgvector search with OPA-derived filters → assemble context)
5. Injects retrieved instructions into block's execution context (via state)
6. Calls block's execute function with enriched state
7. For blocks needing smart execution: routes to Kiro headless

This is the Phase 3 core loop applied per-block automatically. The block executor is what makes "scale to millions" work — each block only sees its OPA-scoped slice of instructions.

**Not yet built.** Currently blocks have hardcoded logic. The block executor wrapper is the pre-4.5 prerequisite that connects blocks to OPA/pgvector.

### Pipeline Executor

Dynamic LangGraph StateGraph construction from pipeline definitions:
- Given a PipelineDef, builds a StateGraph at runtime
- Each node = block execution via the block executor
- State flows via LangGraph Annotation, shaped by pipeline's state type
- PG checkpointer for persistent state across steps (enables interrupt/resume)
- Current `Workflow.ts` gets refactored into this generic executor

### Export Types

YAML export format for Nix reproducibility (UC-MW-16, UC-MW-17):

```typescript
interface InstructionExport {
  readonly id: string
  readonly text: string
  readonly metadata: {
    readonly agent_role: string
    readonly task_type: string
    readonly domain: string
    readonly repo: string | null
  }
  readonly content_hash: string          // MD5 of text field
}

interface PipelineExport {
  readonly id: string
  readonly name: string
  readonly steps: ReadonlyArray<PipelineStep>
}
```

On-disk layout: `workflows/{name}/pipeline.yaml` + `workflows/{name}/instructions/{block}.yaml`

### MCP Server Wrapper

Thin MCP stdio server, separate process. kiro-cli launches it via mcp.json config.
- Exposes tools: `list_blocks`, `run_block`, `list_pipelines`, `run_pipeline`
- Calls kiro-cortex HTTP API internally (keeps processes separate)
- Registered in default.nix mcp.json alongside other MCP servers
- Meta-workflow end step generates SKILL.md files that reference these MCP tools

### Kiro Headless Service

New Effect.Service wrapping Kiro headless API:
- Sends scoped instructions + task to Kiro for smart execution
- Blocks that need reasoning/generation (steering-generate, workflow-suggest) call this
- Interface TBD — need to research Kiro headless API (HTTP? CLI subprocess?)

## Phase Plan

### Phase 0: Database Layer ✅ (commit 75d246a)
- PostgreSQL 18 + pgvector on port 5435 (home-manager user service)
- Effect-TS HttpApi server on port 3100
- `kiro_cortex` database with instructions table + HNSW index

### Phase 1: OpenMemory Migration ✅ (commit 33f656f)
- OpenMemory SQLite → PostgreSQL (`openmemory` database, separate from `kiro_cortex`)
- OM_TIER: smart (896-dim) → deep (768-dim pure Ollama)
- MCP operations validated end-to-end

### Phase 2: Infrastructure Wiring ✅ (commit ab33b12)
- OPA systemd service (port 8181, out-of-store symlink to policies/)
- OpaService: Effect.Service with self-contained HTTP client
- LangGraph StateGraph with initial nodes (policy → vector → assemble → generate)
- HttpApi /test endpoint wiring OPA + LangGraph end-to-end

### Phase 3: Core RAG Loop ✅
Built the core retrieval pipeline:
- Migration 0002: added missing columns (source, repo, effective_date, expiry_date)
- EmbeddingService: Effect Service wrapping Ollama /api/embed (nomic-embed-text, 768-dim)
- InstructionRepo: Effect Service for pgvector cosine search with metadata filters (the DB-split boundary)
- Workflow nodes wired to real services (OPA → embed → search → assemble)
- OPA for access control (allow/deny), SQL WHERE for instruction filtering
- Context assembly with token budgets (chars/4 approximation)
- `/context` endpoint replacing `/test`
- Validated end-to-end with inline psql test data (no persistent seed data)

### Phase 4: MVP-Incremental Build

**Strategy**: Build minimal infrastructure, then MVP meta-workflow, then use meta-workflow to iteratively add features to itself. Each sub-phase is small, git-trackable, and the user relaunches kiro between sub-phases. Repo-analysis is NOT touched until meta-workflow is fully functional.

**Deferred until needed:**
- Kiro headless service — not needed when user is always in the loop via kiro-cli. Required later for autonomous workflows.

**Required before 4.5 (OPA per-block injection):**
- Rename `policies/test.rego` → `policies/access.rego`, update package + OPA query path
- Add `policies/scoping.rego` — per-block instruction filtering
- Build YAML → pgvector startup loader (read `workflows/*/instructions/*.yaml` → embed → upsert)
- Build block executor wrapper (query OPA scoping → pgvector search → inject instructions → execute block)
- This closes the loop: blocks consume their seed instructions via OPA at runtime

#### 4.1: Block Model + Registry
- `BlockDef<S>` — generic over pipeline state, LangGraph node signature, OPA context declaration
- `PipelineDef<S>` — steps, conditions, routing, initial state
- `OpaContext` — agent_role, task_type, domain
- `InstructionExport` / `PipelineExport` — YAML export shapes with content_hash
- `BlockRegistry` — Effect.Service, in-memory Map, search by tag/name/description
- Code convention: `src/{workflow-name}/` for workflow-specific blocks, `src/shared/` for reusable sub-workflows (UC-MW-18)
- Migration: add `content_hash` + `model_version` columns to instructions table
- No execution yet — just the type system, registry, and migration

#### 4.2: Pipeline Executor + HITL
- Refactor Workflow.ts into dynamic StateGraph builder from pipeline definitions
- PG checkpointer for `interrupt()`/`Command({ resume })` HITL support
- Block executor: run block with inputs, get outputs (OPA injection deferred)
- Validate: can define a pipeline, run it, pause/resume via interrupt

#### 4.3: MCP Stdio Wrapper
- Thin MCP server calling HTTP API
- Exposes `list_workflows` + `run_workflow` tools
- Registered in mcp.json for kiro-cli discovery

#### 4.4: MVP Meta-Workflow (4 blocks)
- **route**: classify intent (build/update/refine only — audit deferred)
- **interview**: basic HITL via `interrupt()` — user describes what they want, provides block breakdown manually
- **author**: write instructions to DB with OPA metadata + export to filesystem (UC-MW-16)
- **wire**: create pipeline definition, store in DB + export to filesystem (UC-MW-16)
- First instructions in DB = "how to build workflows" (hand-written seed)
- Supports: build (basic), update (basic), refine
- No research, no optimize, no decompose, no promote — added incrementally
- All file changes use small reviewable stacked commits (UC-MW-15)
- Hand-wired StateGraph (not via `buildPipeline` — this is the bootstrap)
- Code structure: `src/meta-workflow/` for workflow-specific blocks, `src/shared/` for reusable sub-workflows (UC-MW-18)

#### Filesystem Export Format (UC-MW-16, UC-MW-17)
Workflows are reconstructable from YAML files on disk for Nix reproducibility. A fresh system runs `home-manager switch` → kiro-cortex starts → reads YAML → re-embeds via Ollama → seeds DB.

**Decision: re-embed, don't export vectors.** Vectors are derived data (same model + text = same vector). Export only source data:

```
workflows/
  shared/                        # reusable sub-workflows (UC-MW-18)
    stacked-commits/             # any workflow that writes files
      pipeline.yaml
      instructions/
        stage.yaml
        commit.yaml
    # historical-tracking/, etc. added as patterns emerge
  meta-workflow/
    pipeline.yaml              # block order, conditions, routing
    instructions/
      route.yaml               # text + OPA metadata + content_hash
      interview.yaml
      author.yaml
      wire.yaml
  # future workflows added here by meta-workflow
```

Each instruction YAML: `id`, `text`, `metadata` (agent_role, task_type, domain, repo), `content_hash` (MD5 of text).

**Load sequence** (kiro-cortex startup):
1. Read all workflow YAML from `workflows/` directory
2. For each instruction: check DB for matching `content_hash`
3. Match → skip. No match → embed via Ollama → insert/update DB
4. Pipeline definitions: upsert from `pipeline.yaml`
5. OPA policies: already files in `policies/`, loaded by OPA directly

**Model version pinning**: Pin `nomic-embed-text` to specific tag (not `:latest`). Track `model_version` in DB. On model upgrade, re-embed everything (~8 sec at 1K instructions).

**Self-updating** (UC-MW-17): When meta-workflow updates itself, author/wire blocks write to DB AND update `workflows/meta-workflow/` YAML files. User commits changes to git.

#### Pre-4.5: OPA Per-Block Injection (required before meta-workflow self-improves)
- Rename `policies/test.rego` → `policies/access.rego` (update package + query path)
- Add `policies/scoping.rego` — per-block instruction filtering via OPA
- Build YAML → pgvector startup loader (read seed YAMLs → embed → upsert DB)
- Build block executor wrapper (OPA scoping query → pgvector search → inject → execute)
- Blocks consume their seed instructions at runtime — closes the OPA loop

#### 4.5+: Incremental via Meta-Workflow
Each is a sub-phase added by using meta-workflow's update capability (UC-MW-2). User relaunches kiro between each. Order flexible based on what's most useful:
- **decompose** block — propose block structure (currently user provides manually)
- **promote** block — generate SKILL.md + trigger artifacts (currently manual)
- **research** block — external search during design
- **optimize** block — instruction bloat, spaghetti, DRY checks
- **audit** mode in route — UC-MW-13 manual trigger
- **programmatic** mode in route — UC-MW-4/12 short-circuit path
- `policies/isolation.rego` — repo boundary enforcement
- Kiro headless service (when autonomous execution needed)
- Explore replacing zod with Effect Schema → JSON Schema for MCP tool definitions (remove zod dependency)

### Phase 5: Repo-Analysis (Built by Meta-Workflow)
- Use meta-workflow to build repo-analysis as first generated workflow
- Git worktree aware (repo identity by remote origin)
- Instruction scoping (repo-specific vs framework-agnostic, OPA enforced)
- Iterative: uses historical tracking pattern for convention evolution
- Knowledge seeding as a step (detect frameworks → suggest sources → HITL approval → ingest)
- Output workflows TBD (meta-workflow interviews user on what's useful)
- Known knowledge sources: EffectPatterns (300+), effect-solutions (10+)

### Phase 6: Web UI
- LangGraph Studio or custom dashboard
- OPA management interface
- Knowledge graph visualization
- HITL workflow interactions via web (same pattern as kiro-cli chat)

## Effect-TS Patterns

Established patterns:

- `Effect.Service` with `dependencies` array for layer provision
- `NodeHttpClient.layer` in dependencies (self-contained, no agent leak)
- `Schema.TaggedError` for API errors, registered via `.addError()` on endpoints
- `HttpApiBuilder.api(Api).pipe(Layer.provide(groups))` — api needs groups, not reverse
- `HttpLive.pipe(Layer.launch, BunRuntime.runMain)` for server startup
- `effect-language-service diagnostics --project tsconfig.json` for Effect-specific checks
- `sql.and([...conditions])` for dynamic WHERE clause construction
- `sql.unsafe()` for pgvector literal interpolation (vector strings)
- `Schema.optionalWith(Schema.String, { default: () => "value" })` for optional request fields with defaults

## References

- [OPA](https://www.openpolicyagent.org/) — Open Policy Agent
- [LangGraph.js](https://langchain-ai.github.io/langgraphjs/) — Agent orchestration
- [pgvector](https://github.com/pgvector/pgvector) — PostgreSQL vector extension
- [Effect-TS](https://effect.website/) — Functional TypeScript framework
