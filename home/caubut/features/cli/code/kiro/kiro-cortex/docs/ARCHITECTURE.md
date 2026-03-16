# Kiro Cortex Architecture

## Problem

Steering files don't scale. As repos, agents, and policies grow, context windows fill with irrelevant instructions. 35+ files across personal + one work repo = ~31K tokens loaded every session. Most are irrelevant to the current task. The LLM forgets or misapplies rules buried in noise.

## Solution — In One Sentence

RAG over steering files, with policy governance and hybrid workflow orchestration layered on top.

All codified knowledge — steering rules, coding standards, repo conventions — gets parsed into structured rows in a PostgreSQL table (`instructions`), each tagged with metadata and an embedding vector. When a task arrives, kiro-cortex searches for semantically relevant instructions, filters by metadata, trims to a token budget, and returns only what the agent needs. Orchestration uses the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries. A single `run_workflow` MCP tool runs segments, interrupts at boundaries, and resumes — no separate block-level tools needed.

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
- Pre-4.5 (done): Rename test.rego → access.rego. Add scoping.rego. Build block executor wrapper. Wire YAML loader.
- 4.5+: isolation.rego, complex cross-domain rules, per-repo policies.

### Layer 3: Workflow Orchestration (Phase 4)

Hybrid orchestration — three patterns, chosen per-workflow based on characteristics:

#### Deterministic (LangGraph)

For data pipelines with strict ordering, persistent state, and reproducible execution.

```
  ┌─ LangGraph Pipeline ─────────────────────────────────────┐
  │                                                            │
  │  Step 1: Analyze                                           │
  │    OPA input: {agent=analyst, task=analyze, domain=repo}   │
  │    → core loop → instructions about analysis patterns      │
  │                                                            │
  │  Step 2: Code                                              │
  │    OPA input: {agent=developer, task=code, domain=effect}  │
  │    → core loop → instructions about coding standards       │
  │                                                            │
  │  Persistent state across steps (PG checkpointer)           │
  └────────────────────────────────────────────────────────────┘
```

#### Segment Model (How Workflows Actually Execute)

A real end-to-end workflow is composed of **segments**. Each segment is a deterministic LangGraph sub-graph (one or more blocks in strict order). Claude stitches segments together using the Sequential Thinking pattern: call `run_workflow` → read BlockOutput → reason/interact → call `run_workflow` to resume.

**There is only one MCP tool: `run_workflow`.** It runs the workflow's LangGraph graph until it hits an AI-orchestrated boundary (implemented as `interrupt()`), then returns a `BlockOutput` containing:
- What the deterministic segment accomplished
- Context/instructions for what Claude should do at this boundary
- Whether to spawn a subagent, ask the user, or just resume

Claude does its work (reasoning, user interaction, subagent spawning), then calls `run_workflow` with the same `thread_id` to resume the next deterministic segment. LangGraph checkpointing handles all state across interrupt/resume cycles.

```
  Claude (in Kiro CLI)
    │
    ├─ calls run_workflow(id, thread_id) → runs deterministic segment A
    │   LangGraph: block_1 → block_2 → block_3 → interrupt()
    │   Returns: BlockOutput { what_was_done, result, next_step, human_decisions_needed }
    │
    ├─ reads BlockOutput.next_step → "ask user about X"
    │   Claude asks user, gets answer
    │
    ├─ calls run_workflow(id, thread_id) → resumes, runs deterministic segment B
    │   LangGraph: block_4 → block_5 → interrupt()
    │   Returns: BlockOutput { ..., next_step: spawn_subagent("code-review", task) }
    │
    ├─ reads BlockOutput.next_step → spawns subagent via use_subagent
    │   Subagent runs autonomously, returns results
    │
    ├─ calls run_workflow(id, thread_id) → resumes, runs final segment C
    │   LangGraph: block_6 → block_7 → END
    │   Returns: BlockOutput { ..., next_step: complete }
    │
    └─ done
```

**Pattern variants are just different segment configurations:**

| Pattern | Segments | AI Boundaries | Example |
|---------|----------|---------------|---------|
| Pure deterministic | 1 segment | None | Data pipeline: `run_workflow` runs end-to-end |
| Hybrid | N segments | Between segments | Meta-workflow: interview(interrupt) → decompose→optimize(interrupt) → author→wire→promote |
| Pure AI-orchestrated | N single-block segments | Between every block | Exploratory design: each block is its own segment, Claude decides everything |

#### Reusable Segments (Sub-Graphs)

Reusable patterns (UC-MW-18) like stacked-commits and historical-tracking are LangGraph sub-graphs in `src/shared/`. They compose into any workflow as nodes in the parent graph:

```typescript
import { stackedCommitsGraph } from "../shared/stacked-commits.js"

// wire block composes reusable segment into parent workflow graph:
graph.addNode("commit-changes", stackedCommitsGraph)
     .addEdge("author", "commit-changes")
     .addEdge("commit-changes", "promote")
```

At runtime, `run_workflow` traverses the parent graph. When it hits a sub-graph node, LangGraph executes the sub-graph transparently — including any interrupt points within it. State flows through. Checkpointing works across the boundary.

When optimize detects DRY violations, it can recommend: "Extract blocks X and Y into a reusable segment in `shared/`." The wire block then imports and composes them. Reusable segments are parameterizable via state (e.g., stacked-commits receives file paths from the parent workflow's state).

#### Subagent Execution

For autonomous blocks needing LLM reasoning with fresh context. Claude spawns a subagent when `BlockOutput.next_step` says to. Subagents access kiro-cortex + OpenMemory via MCP. Results auto-return to parent.

```
  Parent Claude (main conversation)
    │
    ├─ calls run_workflow → deterministic segment runs → interrupt()
    │   BlockOutput.next_step = { type: "spawn_subagent", agent: "...", task: "..." }
    │
    ├─ spawns subagent via use_subagent
    │   └─ Subagent (fresh context, kiro-cortex MCP + OpenMemory MCP)
    │       ├─ calls kiro-cortex for OPA-scoped instructions
    │       ├─ generates output autonomously
    │       └─ returns results to parent
    │
    ├─ calls run_workflow(thread_id) → resumes next segment
    │
    └─ presents results to user for approval
```

**Subagent constraints** (meta-workflow must know these when designing workflows):
- ✅ read, write, shell, code, MCP tools
- ❌ interactive tasks (no back-and-forth with user)
- ❌ web_search, web_fetch, introspect, thinking, todo_list, use_aws, grep, glob
- Blocks requiring these ❌ tools must run in parent conversation or deterministic pipeline
- Reference: https://kiro.dev/docs/cli/chat/subagents/#tool-availability

#### Pattern Selection

Meta-workflow codifies this knowledge in its instructions so it can recommend the right pattern when designing new workflows. The segment model means most workflows are hybrid — the question is how many AI boundaries they need.

#### NextStep Design (Q2 Resolution)

`BlockOutput.next_step` is a discriminated union that tells Claude exactly what to do after a deterministic segment completes. This follows the Sequential Thinking MCP pattern where structured output (not free text) drives Claude's next action.

**Variants:**

| Type | Claude Action | When Used |
|------|--------------|-----------|
| `resume` | Call `run_workflow` with same `thread_id` | Next deterministic segment ready |
| `spawn_subagent` | Call `use_subagent` with agent + task | Autonomous block needs LLM reasoning |
| `ask_user` | Present question (with optional choices) | Human decision needed before continuing |
| `complete` | Present summary, stop | Workflow finished |

**Full BlockOutput shape:**
```typescript
interface BlockOutput {
  what_was_done: string           // summary of segment accomplishment
  result: unknown                 // block-specific data
  next_step: NextStep             // discriminated union (see below)
  human_decisions_needed: string[] // decisions needed (may be empty)
}

type NextStep =
  | { type: "resume"; context?: string }
  | { type: "spawn_subagent"; agent: string; task: string }
  | { type: "ask_user"; question: string; options?: string[] }
  | { type: "complete"; summary: string }
```

**Design rationale:**
- Structured over free text: Claude maps `type` directly to an action — no interpretation ambiguity
- Matches Sequential Thinking MCP's `outputSchema` pattern (structured fields → Claude decides)
- Machine-readable: future automation can act on NextStep without LLM interpretation
- Extensible: add new variants without breaking existing ones
- `resume.context` is optional UX hint about what's coming next (not required for correctness)
- `ask_user.options` is optional — omit for open-ended questions, include for structured choices

**Data flow at AI boundaries:**
1. `run_workflow` runs deterministic segment → hits `interrupt()` → returns `BlockOutput`
2. Claude reads `next_step.type` and acts accordingly
3. When resuming, Claude passes results (user answer, subagent output) via `run_workflow`'s `input` param
4. LangGraph's interrupt/resume mechanism handles state continuity

**References:**
- Sequential Thinking MCP outputSchema: https://www.npmjs.com/package/@modelcontextprotocol/server-sequential-thinking
- Anthropic advanced tool use patterns: https://www.anthropic.com/engineering/advanced-tool-use

## Component Responsibilities

| Component | Manages | Talks to | Stateful? |
|-----------|---------|----------|-----------|
| **kiro-cortex** | Instructions table, context assembly, workflow orchestration | PostgreSQL, OPA, Ollama | Yes (PG) |
| **PostgreSQL** | Data storage (instructions + embeddings + workflow state) | Only responds to kiro-cortex | Yes |
| **OPA** | Policy rules (Rego files) | Only responds to kiro-cortex | No (stateless) |
| **Ollama** | Embedding models | Only responds to kiro-cortex | No (stateless) |
| **Kiro CLI** | User interaction, subagent lifecycle, hooks | Calls kiro-cortex via MCP | Session state |
| **Subagents** | Autonomous block execution with fresh context | kiro-cortex MCP, OpenMemory MCP | No (ephemeral) |
| **Hooks** | Supplementary OPA (AgentSpawn, PreToolUse) | OPA, kiro-cortex | No (per-event) |
| **LangGraph** | Deterministic pipeline graph definition and step sequencing | Embedded in kiro-cortex | State in PG |

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
- **MCP tool** — from kiro-cli (MCP stdio wrapper). Claude calls block tools in a loop for AI-orchestrated workflows.
- **HTTP API** — direct POST to `/blocks/{id}/run`. Used by MCP wrapper internally.
- **Pipeline step** — from LangGraph orchestration (deterministic mode). Output feeds next step's state.
- **Subagent** — Kiro spawns a subagent with custom agent config + kiro-cortex MCP. For autonomous blocks needing LLM reasoning with fresh context.

All share the same block implementation and OPA-scoped instruction injection. Context size is configurable per-call via `token_budget` parameter.

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

### Orchestration & Execution Use Cases

- **UC-MW-19**: Meta-workflow selects orchestration pattern (deterministic vs AI-orchestrated vs subagent) based on workflow characteristics during interview. Knowledge of when to use each pattern is codified in meta-workflow's instructions, not hardcoded. Validation: a data pipeline gets deterministic, an interactive design workflow gets AI-orchestrated, a code generation task gets subagent.
- **UC-MW-20**: Meta-workflow designs custom Kiro agent configs per workflow — specialized agents, not one generic worker. Agent configs include: tools/allowedTools, toolsSettings.subagent (availableAgents, trustedAgents), hooks (agentSpawn, preToolUse with matchers), mcpServers (kiro-cortex for instruction access), resources (SKILL.md, relevant files), prompt (workflow-specific system prompt). Considers reusable agent patterns as lego blocks. When self-improving (4.5+), can identify need for new agents or refine existing ones.
- **UC-MW-21**: AI-orchestrated blocks return structured output (`BlockOutput` with `next_step: NextStep`) so Claude can reason about next steps and decide the next MCP call. Convention similar to Sequential Thinking MCP pattern.
- **UC-MW-22**: Autonomous blocks execute in Kiro subagents with fresh context. Mechanism: kiro-cortex returns BlockOutput with subagent spawn info (agent name, task) → Claude reads it and calls `use_subagent`. Subagents access kiro-cortex + OpenMemory via MCP. Results auto-return to parent. Meta-workflow must know subagent constraints and design around them.
- **UC-MW-23**: Hooks supplement OPA as lightweight context injection and access control. Hooks are defined per-agent in agent config JSON; hook scripts (actual logic) are reusable and live in `~/.kiro/hooks/`. AgentSpawn injects OPA user profile at session start. PreToolUse gates kiro-cortex MCP calls against OPA access policy. Agent configs reference scripts with workflow-specific matchers.
- **UC-MW-24**: Single MCP tool design — `run_workflow` is the only tool needed. It runs deterministic segments (LangGraph sub-graphs) until hitting an AI boundary (`interrupt()`), returns `BlockOutput` with context for what Claude should do, Claude does its work (reason, ask user, spawn subagent), then calls `run_workflow` with same `thread_id` to resume. LangGraph checkpointing handles all state. No separate `run_block` tool — AI boundaries are interrupt points in the graph, not separate tool calls. Reusable segments (UC-MW-18) compose as sub-graph nodes; `run_workflow` traverses them transparently.
- **UC-MW-25**: Meta-workflow proposes hooks when designing workflows. Can propose workflow-specific hooks (e.g., preToolUse that validates domain constraints) or identify new reusable hooks (when a pattern emerges across workflows). Reusable hook scripts go in shared location (`~/.kiro/hooks/`); workflow-specific hooks are generated alongside agent configs.
- **UC-MW-26**: Workflow trigger selection during interview. Meta-workflow asks: "How will this workflow be triggered?" Options: (A) **Dedicated agent** — user switches to it explicitly, good for focused work with specialized context; (B) **Skill** — default agent activates it when request matches description, good for "Claude identifies and uses" workflows. This determines whether promote block generates an agent config (`.kiro/agents/`) or a skill (`.kiro/skills/` or `~/.kiro/skills/`). Skills follow the [Agent Skills standard](https://agentskills.io).
- **UC-MW-27**: Meta-workflow itself is a top-level agent (not always in context). User switches to meta-workflow agent when designing/updating workflows. This keeps meta-workflow's instructions out of default context — critical for the 1M tiny instructions goal. Meta-workflow agent config lives in `~/.kiro/agents/meta-workflow.json`.
- **UC-MW-28**: Context optimization is a first-class design goal. Meta-workflow proposes the right artifact type (agent, skill, subagent, MCP) based on context budget impact. Guidelines: (1) Skills for on-demand activation by description matching; (2) Agents for dedicated focused work; (3) Subagents for autonomous blocks needing fresh context; (4) MCPs for external tools not in context until called. The 1M instructions goal requires aggressive context management.
- _(Add more use cases here as they emerge)_

### Description

The meta-workflow is a hand-built collection of tools for the workflow lifecycle. It is the first real customer of the OPA pipeline — its instructions ("how to build workflows") are the first content in the instructions table.

**Human-in-the-loop by design.** The meta-workflow interviews the user on goals, proposes a decomposition into blocks, and iterates until the user approves. This HITL pattern works via kiro-cli chat (MCP tool calls or direct conversation).

### Orchestration Pattern Knowledge

Meta-workflow must codify knowledge about orchestration patterns in its instructions so it can recommend the right approach when designing new workflows:

- **When to recommend deterministic (LangGraph)**: strict ordering required, data processing pipelines, reproducibility needed, persistent state across sessions. These become single-segment workflows — `run_workflow` runs end-to-end with no interrupts.
- **When to recommend hybrid (segments)**: most real workflows. Deterministic segments (LangGraph sub-graphs) stitched by Claude orchestration at AI boundaries. `run_workflow` runs each segment, interrupts at boundaries, Claude reasons/interacts, resumes. Example: interview(interrupt) → decompose→optimize(interrupt) → author→wire→promote.
- **When to recommend pure AI-orchestrated**: rare. Every block is its own single-block segment with AI boundaries between all of them. Use only when ordering is truly flexible and every step needs judgment. Degenerate case of hybrid.
- **When to recommend subagents**: autonomous blocks needing LLM reasoning, fresh context beneficial, parallel execution, long-running background tasks. Triggered by `BlockOutput.next_step` at AI boundaries — Claude reads it and calls `use_subagent`.
- **Subagent constraints to design around**: no interactive tasks, no web_search/web_fetch/introspect/thinking/todo_list/use_aws/grep/glob — blocks requiring these must run in parent conversation or deterministic pipeline (ref: https://kiro.dev/docs/cli/chat/subagents/#tool-availability)
- **Agent design**: specialized agents per workflow (not one generic worker). Agent configs are comprehensive: tools, hooks, subagent settings, MCP servers, resources, prompt. Consider reusable agent patterns as lego blocks. When self-improving, meta-workflow should identify when new agents, skills, hooks, or MCPs are needed.
- **Skills vs agents (UC-MW-26)**: during interview, meta-workflow asks how the workflow will be triggered. Dedicated agent = user switches explicitly (focused context). Skill = default agent activates on request match (on-demand). This determines what promote block generates. Skills follow the [Agent Skills standard](https://agentskills.io) — SKILL.md with frontmatter (name, description) + optional references/. Ref: https://kiro.dev/docs/cli/skills/
- **Context optimization (UC-MW-28)**: 1M instructions goal requires aggressive context management. Meta-workflow proposes the right artifact type based on context budget: skills (on-demand by description), agents (dedicated focus), subagents (fresh context), MCPs (external, not in context until called). Meta-workflow itself is a top-level agent (UC-MW-27) — not always loaded.
- **Hooks in agent configs**: hooks are per-agent (defined in agent config JSON), not standalone. Hook scripts are reusable (`~/.kiro/hooks/`); agent configs reference them with workflow-specific matchers. Meta-workflow proposes hooks during design (UC-MW-25).
- **Structured output convention for AI-orchestrated blocks**: blocks return `BlockOutput` with `next_step: NextStep` — a discriminated union (Q2 resolved). Claude maps each variant to a specific action. See "NextStep Design" below.
- **Single MCP tool (UC-MW-24)**: `run_workflow` is the only tool. Runs deterministic segments, interrupts at AI boundaries, returns BlockOutput. Claude resumes with same thread_id. No separate `run_block` tool. Reusable segments (sub-graphs from `src/shared/`) compose transparently — LangGraph traverses them including their internal interrupt points.

This knowledge lives in meta-workflow's seed instructions (YAML), not hardcoded in block logic. When meta-workflow self-improves (4.5+), it can refine these patterns.

### Capabilities

- **Interview**: Understand user goals — what problem the workflow solves, what triggers it, what it outputs. Help the user discover and articulate the problem statement if they have a vague idea. Help identify concrete use cases through examples, edge cases, and probing questions. Propose blocks and pipeline structure. Assess orchestration needs (interactive vs autonomous, ordering constraints) to recommend deterministic vs AI-orchestrated vs hybrid. User approves/refines.
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
| Orchestration model | Hybrid (LangGraph + AI-orchestrated + subagents) | Deterministic for pipelines, AI for interactive, subagents for autonomous |
| Smart executor | Kiro CLI subagents (not custom headless service) | Kiro manages lifecycle, no process management code needed |
| Ollama role | Embeddings + classification only | Cheap/fast for bulk preprocessing |
| OPA in Phase 3 | Access control only (allow/deny) | SQL WHERE sufficient for filtering until policy complexity grows |
| OPA in Phase 5 | Generates filtering criteria per step | Complex policies need declarative rules |
| Hooks | Supplementary OPA (AgentSpawn + PreToolUse) | Lightweight CLI-layer injection, not a replacement for block executor |
| Single DB | PostgreSQL (metadata + vectors together) | Split via Effect Service boundary when scaling demands it |
| Vector index | HNSW over IVFFlat | Better accuracy, no training needed, works at any scale |
| Token estimation | chars/4 approximation | Upgrade to tiktoken when accuracy matters |
| Context budget | Caller-specified per request | Task complexity determines budget |
| Hosting | Self-hosted, NixOS/Home Manager | Full control, privacy, no vendor lock-in |
| Runtime | Bun + pnpm, Effect-TS | User preference, type safety |
| HTTP clients | HttpApi + Schema (not raw HttpClient) | Full type safety on request/response; Schema validates at runtime, no `as any` casts |
| API client pattern | Context.Tag + Layer.effect (not Effect.Service) | Client type inferred from HttpApiClient.make; Effect.Service wrapper is unnecessary indirection |
| Envelope handling | Schema.transform (not transformResponse) | transformResponse runs after decode and erases types; Schema.transform preserves full type safety |
| Error handling | .addError() with real API error schemas | Model what the external API actually returns on error; no manual mapError |
| Code organization | Domain folders with barrel files | Discoverability for humans and AI; each domain is self-contained |
| Error co-location | Domain-scoped errors (not monolithic error file) | Errors live with their domain; no cross-domain imports for error types |
| Web UI | Read-only dashboard (afterthought) | Local CLI is primary interface; local-first development experience preferred |

## Code Conventions

### TypeScript Configuration

- `verbatimModuleSyntax: true` — use `export type` for type-only re-exports in barrel files
- `exactOptionalPropertyTypes: true` — optional properties must be explicitly `undefined` or omitted
- No `as any` casts. **One exception:** `CompiledPipeline` in `workflow/Workflow.ts` (LangGraph's compiled graph type is not fully generic)

### Package Structure

Code is organized by domain, not by technical layer. Each domain folder has a barrel `index.ts` with rich TSDoc describing the domain's purpose, public API, and relationship to other domains.

```
src/
  opa/            → OPA policy client (access control + scoping)
  embedding/      → Ollama embedding client (text → vector)
  instruction/    → Instruction data layer (pgvector Repo + YAML Loader)
  workflow/       → Orchestration engine (Block, Registry, Executor, Pipeline, Workflow types)
  meta-workflow/  → Meta-workflow block implementations (route, interview, author, wire, graph, state)
  Sql.ts          → Shared PostgreSQL connection layer
  index.ts        → HTTP server (composes all domains)
  mcp.ts          → MCP stdio server (standalone process, zod-only)
  migrations/     → Database migrations
```

**Barrel file convention:** Every domain folder exports its public API through `index.ts`. The barrel file MUST have a module-level TSDoc comment explaining: what the domain does, what it exports, and how it relates to other domains. Barrel files are the primary navigation aid for both humans and AI.

### HTTP Clients via HttpApi + Schema

All HTTP calls to external services (OPA, Ollama, etc.) use `HttpApi` + `HttpApiClient.make()` with Effect `Schema` types for request and response bodies. This gives compile-time AND runtime type safety — no `as any` casts, no manual JSON parsing.

**Pattern:**
1. Define `Schema` types matching the real external API (keep schemas honest)
2. Use `Schema.transform` to handle envelope unwrapping (e.g., OPA's `{ result: T }` → `T`) at the schema level — keeps endpoint success types clean
3. Use `.addError(ErrorSchema)` on endpoints with schemas matching the external API's actual error shape — no manual `mapError`
4. Define the API shape using `HttpApiEndpoint` + `HttpApiGroup` + `HttpApi`
5. Create a `Context.Tag` for the client type (inferred from `HttpApiClient.make`)
6. Export `const layer = Layer.effect(Tag, HttpApiClient.make(...))` — no `Effect.Service` wrapper needed

**Client pattern (no Effect.Service):**
```typescript
const make = HttpApiClient.make(MyApi, { baseUrl: "http://..." })
export class MyClient extends Context.Tag("MyClient")<MyClient, Effect.Effect.Success<typeof make>>() {}
export const layer = Layer.effect(MyClient, make).pipe(Layer.provide(NodeHttpClient.layer))
```

**Why Context.Tag over Effect.Service for API clients:** The client type is fully inferred from `HttpApiClient.make`. An `Effect.Service` wrapper would just re-export the same methods — unnecessary indirection. `Context.Tag` + `Layer.effect` is the minimal injectable pattern.

**Why Schema.transform over transformResponse:** `HttpApiClient.make`'s `transformResponse` runs AFTER schema decoding and erases types to `Effect<unknown, unknown>`. `Schema.transform` handles envelope unwrapping at the schema level, preserving full type safety.

**Why not raw HttpClient:** Raw `HttpClient` requires manual JSON parsing and `as any` casts. `HttpApi` + `HttpApiClient` covers both request and response typing.

**Exception:** `src/mcp.ts` uses plain `fetch` because it runs as a standalone MCP stdio process outside the Effect runtime. Zod is allowed only in this file for MCP SDK compatibility.

### Layer Export Convention

Every module that provides a `Layer` MUST export it as `export const layer = ...`. This is the standard Effect pattern for discoverability and composition.

- For `Context.Tag` + `Layer.effect`: `export const layer = Layer.effect(Tag, make).pipe(...)`
- For `Effect.Service`: `export const layer = ServiceName.Default`
- Callers compose via `Layer.provide(MyModule.layer)` — consistent across all modules

### Commenting Standards

All TypeScript files use consistent documentation for both human and AI readers:

**TSDoc comments (required on every export):**
- Interfaces, types, classes, functions, constants
- Describe WHAT it is and WHY it exists
- Include `@param`, `@returns`, `@example` where useful

**Inline comments (required for non-trivial code):**
- Explain the reasoning, not the syntax
- Flag non-obvious constraints: "OPA wraps results in { result: ... }"
- Mark architectural boundaries: "--- OPA scoping ---"

**AI-readable annotations:**
- `// ARCH: ...` — architectural context (why this design choice)
- `// CONSTRAINT: ...` — non-obvious constraint that must be preserved
- `// EXTERNAL: ...` — documents external API behavior/quirks
- These help AI assistants understand intent when modifying code

**JSDoc gotcha:** Avoid glob patterns containing `/*` in JSDoc comments — the `*/` sequence closes the comment block prematurely. Use prose descriptions instead of literal glob syntax.

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
7. For blocks needing smart execution: routes to Kiro subagent (autonomous) or returns structured output for AI orchestration

This is the Phase 3 core loop applied per-block automatically. The block executor is what makes "scale to millions" work — each block only sees its OPA-scoped slice of instructions.

**Built.** `BlockExecutor.ts` wraps each block: OPA scoping → pgvector search → inject `_context` into state → execute. `PipelineExecutor` routes all nodes through the block executor. `InstructionLoader.ts` reads seed YAML at startup, embeds via Ollama, upserts with content_hash idempotency.

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

### Execution Environments

Blocks run in different environments depending on their needs:

| Environment | When | How | Limitations |
|-------------|------|-----|-------------|
| **Inline** | Simple blocks, routing, state transforms | Block runs in kiro-cortex process via `Effect.runPromise` | No LLM reasoning |
| **Subagent** | Autonomous blocks needing LLM reasoning | Kiro spawns subagent with custom agent config + kiro-cortex MCP | No interactive, no web_search, no grep/glob |
| **AI-orchestrated** | Interactive workflows, judgment-based sequencing | Claude calls block MCP tools in a loop, blocks return structured output | Non-deterministic ordering |

**Subagents replace the originally planned Kiro headless service.** Kiro manages the subagent lifecycle (spawning, progress tracking, result aggregation, agent approval). No process management code needed in kiro-cortex.

**Custom agent configs per workflow** (UC-MW-20): Meta-workflow designs specialized agents rather than one generic worker. Agent configs live alongside workflow definitions and can be reusable lego blocks (e.g., a stacked-commits agent used by any file-writing workflow).

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
- Hooks integration (AgentSpawn + PreToolUse for supplementary OPA) — not needed until workflows are running end-to-end

**Required before 4.5 (OPA per-block injection) — DONE:**
- ✅ Rename `policies/test.rego` → `policies/access.rego`, update package + OPA query path
- ✅ Add `policies/scoping.rego` — per-block instruction filtering
- ✅ Build YAML → pgvector startup loader (read `workflows/*/instructions/*.yaml` → embed → upsert)
- ✅ Build block executor wrapper (query OPA scoping → pgvector search → inject instructions → execute block)
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

#### Pre-4.5: OPA Per-Block Injection ✅
- ✅ Rename `policies/test.rego` → `policies/access.rego` (update package + query path)
- ✅ Add `policies/scoping.rego` — per-block instruction filtering via OPA
- ✅ Build YAML → pgvector startup loader (read seed YAMLs → embed → upsert DB)
- ✅ Build block executor wrapper (OPA scoping query → pgvector search → inject → execute)
- Blocks consume their seed instructions at runtime — closes the OPA loop

#### 4.5: Meta-Workflow Completion ✅
Added remaining blocks to make meta-workflow fully functional:
- **decompose** — registry search for reuse, block proposal via interrupt, programmatic mode (UC-MW-4/12), execution_env recommendation (UC-MW-19)
- **research** — interrupt-based external knowledge gathering (UC-MW-7), pass-through when not needed, feeds back into interview loop
- **optimize** — rule-based bloat (UC-MW-8), spaghetti (UC-MW-9), DRY (UC-MW-10) checks with HITL approval, needs_redesign loop
- **promote** — generates trigger artifacts based on UC-MW-26 interview answer: SKILL.md (for skill trigger) or agent config JSON (for dedicated agent). HITL artifact selection.
- Updated route with audit (UC-MW-13) and programmatic (UC-MW-4) modes
- Updated interview with research loop support and audit mode
- Full graph wiring: interview↔research loop, decompose→optimize→author with redesign loop

#### 4.5+: Incremental Enhancements
Remaining items to add incrementally as needed:
- **decompose** block — ✅ (4.5)
- **promote** block — ✅ (4.5)
- **research** block — ✅ (4.5)
- **optimize** block — ✅ (4.5)
- **audit** mode in route — ✅ (4.5)
- **programmatic** mode in route — ✅ (4.5)
- Subagent + hooks integration (UC-MW-20, 22, 23, 24, 25) — merged: agent configs are the central artifact containing tools, hooks, subagent settings, MCP servers. Promote block generates comprehensive agent configs. Shared hook scripts in `~/.kiro/hooks/`. Single `run_workflow` MCP tool with interrupt/resume at AI boundaries (Q1 resolved).

**Resolved: Q1 — single `run_workflow` tool (interrupt/resume)**
Workflows are composed of deterministic LangGraph segments. `run_workflow` runs until an AI boundary (`interrupt()`), returns `BlockOutput`, Claude does its work, calls `run_workflow` with same `thread_id` to resume. No separate `run_block` tool. Reusable segments (UC-MW-18) are sub-graphs that compose transparently. See "Segment Model" in orchestration section.

**Resolved: Q2 — structured NextStep discriminated union**
`BlockOutput.next_step` uses a discriminated union (not free text). Claude maps each variant to a specific action:

```typescript
type NextStep =
  | { type: "resume"; context?: string }        // call run_workflow with same thread_id
  | { type: "spawn_subagent"; agent: string; task: string }  // call use_subagent
  | { type: "ask_user"; question: string; options?: string[] }  // present to user
  | { type: "complete"; summary: string }       // workflow done
```

Design follows Sequential Thinking MCP pattern: structured outputSchema that Claude parses to decide its next action. No free text interpretation needed. See references below.

**Hook Conventions:**

Hooks are per-agent (defined in agent config JSON `hooks` field), not standalone scripts. Reusable hook scripts live in `~/.kiro/hooks/` and agent configs reference them with workflow-specific matchers.

Hook triggers available:
- `agentSpawn` — when agent is activated (e.g., `git status`, load context)
- `userPromptSubmit` — when user submits a prompt
- `preToolUse` — before tool execution, can block (use `matcher` for tool name pattern)
- `postToolUse` — after tool execution (e.g., `cargo fmt` after `fs_write`)
- `stop` — when assistant finishes responding (e.g., `npm test`)

Hook matchers use internal tool names: `fs_read`, `fs_write`, `execute_bash`, `use_aws`, etc.

Example hook script convention for `~/.kiro/hooks/`:
```
~/.kiro/hooks/
├── audit-bash.sh       # Log bash commands: preToolUse matcher "execute_bash"
├── audit-aws.sh        # Log AWS calls: preToolUse matcher "use_aws"
├── format-on-write.sh  # Auto-format: postToolUse matcher "fs_write"
└── spawn-context.sh    # Load context: agentSpawn (no matcher)
```

Agent configs reference these:
```json
{
  "hooks": {
    "agentSpawn": [{ "command": "~/.kiro/hooks/spawn-context.sh" }],
    "preToolUse": [{ "matcher": "execute_bash", "command": "~/.kiro/hooks/audit-bash.sh" }]
  }
}
```

Ref: https://kiro.dev/docs/cli/custom-agents/configuration-reference (hooks field), https://kiro.dev/docs/cli/hooks

**BlockOutput → Claude → Action Flow:**

When `run_workflow` returns a `BlockOutput` at an AI boundary, Claude reads `next_step.type` and maps it to a concrete action:

```
run_workflow returns BlockOutput
  ├── next_step.type === "resume"
  │   → Claude calls run_workflow(thread_id, input: context)
  │
  ├── next_step.type === "spawn_subagent"
  │   → Claude calls use_subagent(agent: next_step.agent, task: next_step.task)
  │   → Subagent runs autonomously with fresh context
  │   → Claude resumes workflow with subagent output
  │
  ├── next_step.type === "ask_user"
  │   → Claude presents next_step.question (with options if provided)
  │   → User responds
  │   → Claude resumes workflow with user answer
  │
  └── next_step.type === "complete"
      → Claude presents next_step.summary
      → Workflow done
```

Agent config prompts should include this instruction pattern so Claude knows how to handle BlockOutput:
```
When run_workflow returns a BlockOutput:
- If next_step.type is "resume": call run_workflow with the same thread_id
- If next_step.type is "spawn_subagent": call use_subagent with the specified agent and task
- If next_step.type is "ask_user": present the question to the user, then resume with their answer
- If next_step.type is "complete": present the summary — workflow is done
```

Subagent constraints to encode in prompts: subagents cannot use web_search, web_fetch, introspect, thinking, todo_list, use_aws, grep, glob, or interactive tools. Blocks requiring these must run in parent conversation or deterministic pipeline. Ref: https://kiro.dev/docs/cli/chat/subagents/#tool-availability

**Comprehensive Agent Config Template:**

Promote block generates agent configs with these fields (ref: https://kiro.dev/docs/cli/custom-agents/configuration-reference):

```json
{
  "name": "<workflow>-agent",
  "description": "<workflow description>",
  "model": "auto",
  "prompt": "file://./prompts/<workflow>-agent.md",
  "tools": ["*"],
  "allowedTools": ["@openmemory", "@sequentialthinking", "fs_read", "code"],
  "includeMcpJson": true,
  "mcpServers": {},
  "resources": [
    "skill://.kiro/skills/**/SKILL.md",
    "file://.kiro/steering/**/*.md"
  ],
  "hooks": {
    "agentSpawn": [{ "command": "git status" }]
  },
  "keyboardShortcut": "<optional>",
  "welcomeMessage": "<workflow-specific greeting>"
}
```

Fields promote block should populate per workflow:
- `tools`: restrict to only what the workflow needs (not always `*`)
- `allowedTools`: pre-approve tools the workflow uses frequently
- `mcpServers`: add kiro-cortex MCP if workflow uses instruction DB
- `resources`: include workflow-specific skills and steering files
- `hooks`: add workflow-appropriate hooks (audit, format, context loading)
- `prompt`: generate a prompt file with BlockOutput handling instructions + workflow-specific guidance

**SKILL.md Template:**

Promote block generates skills following the [Agent Skills standard](https://agentskills.io) (ref: https://kiro.dev/docs/cli/skills/):

```markdown
---
name: <workflow-name>
description: <activation description — Kiro matches this against user requests>
---

# <Workflow Name>

<workflow description>

## Trigger

- **Automatic**: Activated when request matches description above

## Workflow

<block-by-block instructions>

## MCP Tools

- `run_workflow` with workflow_id: "<workflow-name>"
```

Skill locations:
- `.kiro/skills/<name>/SKILL.md` — workspace-specific
- `~/.kiro/skills/<name>/SKILL.md` — global (personal)

Optional `references/` folder for detailed docs loaded on demand.

Custom agents must explicitly include skills via `resources`:
```json
{ "resources": ["skill://.kiro/skills/**/SKILL.md", "skill://~/.kiro/skills/**/SKILL.md"] }
```

**Implementation remaining:**
- Phase 4.5+ complete. All items implemented or documented.
- Next: Meta-workflow self-maintenance validation, then Phase 5

### Meta-Workflow Self-Maintenance Gap Analysis (2026-03-16)

Before Phase 5, validate that meta-workflow can maintain itself. Gap analysis performed:

**Critical Gaps (Fixed):**
- G1: ✅ kiro-cortex MCP tools (`@kiro-cortex`) added to `allowedTools`
- G2: ✅ Self-identification added to prompt ("Your workflow ID is meta-workflow")
- G3: ✅ Prompt moved to `file://./prompts/meta-workflow.md` for maintainability
- G4: ✅ agentSpawn hook enhanced (git log + status)
- G5: ✅ Resource paths fixed (absolute with triple slash `file:///`)
- G6: ✅ `toolsSettings.fs_write.allowedPaths` added for write restrictions
- G9: ✅ `fs_write`, `execute_bash`, git tools added to `allowedTools`

**Important Gaps (Documented, Not Yet Implemented):**
- G7: UC-MW-15,16,17 (filesystem export/import) — prerequisite for true self-maintenance. Without these, DB changes don't persist to disk. **Blocking for full self-maintenance.**
- G8: knowledgeBase resource for ARCHITECTURE.md — added but needs testing

**Enhancement Ideas (Future):**
- E1: ✅ Pre-gen prompt file with interaction templates — done
- E2: userPromptSubmit hook for dynamic context injection — deferred
- E3: ✅ welcomeMessage made more actionable

**Items for Interaction-Analysis (Record Only):**
- F1: Suggest "workflow-audit" skill — periodic optimization of all workflows
- F2: Suggest "workflow-metrics" subagent — track workflow usage patterns
- F3: Suggest "pattern-detector" skill — identify common patterns across workflows for DRY
- F4: Meta-workflow should analyze its own interaction patterns to improve interview questions

**Validation Checklist (Before Phase 5):**
1. [ ] Switch to meta-workflow agent (Ctrl+Shift+M)
2. [ ] Verify `list_workflows` works without permission prompt
3. [ ] Verify agent can identify itself in workflow list
4. [ ] Test update mode on meta-workflow itself
5. [ ] Verify prompt file loads correctly
6. [ ] Verify knowledgeBase resource indexes ARCHITECTURE.md

**Blocking Issue for Full Self-Maintenance:**
UC-MW-16/17 (filesystem export) not implemented. Changes to meta-workflow in DB won't persist to disk. Current workaround: manually update YAML exports. True self-maintenance requires implementing export blocks.

### Phase 5: Repo-Analysis (Built by Meta-Workflow)
- Use meta-workflow to build repo-analysis as first generated workflow
- Git worktree aware (repo identity by remote origin)
- Instruction scoping (repo-specific vs framework-agnostic, OPA enforced)
- Iterative: uses historical tracking pattern for convention evolution
- Knowledge seeding as a step (detect frameworks → suggest sources → HITL approval → ingest)
- Output workflows TBD (meta-workflow interviews user on what's useful)
- Known knowledge sources: EffectPatterns (300+), effect-solutions (10+)

### Phase 6: Web Dashboard (Read-Only, Afterthought)
- Read-only DB visualizer: instruction browser, workflow status, pipeline execution history
- OPA policy viewer
- Knowledge graph visualization
- No HITL interactions — all workflow interaction via kiro-cli
- Explore replacing zod 4 with Effect Schema → JSON Schema for MCP tool definitions

## Effect-TS Patterns

Established patterns:

- `Context.Tag` + `Layer.effect` for external API clients (OPA, Ollama) — type inferred from `HttpApiClient.make`, no `Effect.Service` wrapper
- `Effect.Service` with `dependencies` array for infrastructure services (BlockRegistry, InstructionRepo) that have custom logic beyond a client
- Every module exporting a Layer: `export const layer = ...` (Tag-based: `Layer.effect(Tag, make)`, Service-based: `ServiceName.Default`)
- `Schema.transform` for envelope unwrapping (e.g., OPA `{ result: T }` → `T`) — keeps endpoint success types clean
- `.addError(ErrorSchema)` on `HttpApiEndpoint` with schemas matching external API error shapes — no manual `mapError`
- `NodeHttpClient.layer` in dependencies / `Layer.provide` (self-contained, no agent leak)
- `Schema.TaggedError` for domain errors, co-located with their domain module (not a monolithic error file)
- `HttpApiBuilder.api(Api).pipe(Layer.provide(groups))` — api needs groups, not reverse
- `HttpLive.pipe(Layer.launch, BunRuntime.runMain)` for server startup
- `effect-language-service diagnostics --project tsconfig.json` for Effect-specific checks
- `sql.and([...conditions])` for dynamic WHERE clause construction
- `sql.unsafe()` for pgvector literal interpolation (vector strings)
- `Schema.optionalWith(Schema.String, { default: () => "value" })` for optional request fields with defaults

## Development

### Commands

```bash
pnpm run check          # runs check:tsc + check:els in parallel
pnpm run check:tsc      # TypeScript compiler
pnpm run check:els      # effect-language-service diagnostics
```

Run `pnpm run check` after every commit to catch both TypeScript and Effect-specific errors.

## References

### Core Dependencies
- [OPA](https://www.openpolicyagent.org/) — Open Policy Agent
- [LangGraph.js](https://langchain-ai.github.io/langgraphjs/) — Agent orchestration (interrupt/resume, sub-graphs, checkpointing)
- [pgvector](https://github.com/pgvector/pgvector) — PostgreSQL vector extension
- [Effect-TS](https://effect.website/) — Functional TypeScript framework
- [MCP SDK](https://www.npmjs.com/package/@modelcontextprotocol/sdk) — Model Context Protocol server/client

### Design Influences
- [Sequential Thinking MCP](https://www.npmjs.com/package/@modelcontextprotocol/server-sequential-thinking) — Structured outputSchema pattern for Claude self-orchestration (influenced NextStep design)
- [Anthropic: Advanced Tool Use](https://www.anthropic.com/engineering/advanced-tool-use) — Tool Search, Programmatic Tool Calling, Tool Use Examples (informed structured output decision over free text)
- [Anthropic: Building Effective Agents](https://www.anthropic.com/research/building-effective-agents) — Agent design patterns
- [Kiro CLI Subagent Docs](https://kiro.dev/docs/cli/chat/subagents/#tool-availability) — Subagent tool constraints (shaped block execution routing)
- [Kiro CLI Skills Docs](https://kiro.dev/docs/cli/skills/) — Skills vs agents, SKILL.md format, activation by description matching
- [Agent Skills Standard](https://agentskills.io) — Open standard for portable instruction packages
