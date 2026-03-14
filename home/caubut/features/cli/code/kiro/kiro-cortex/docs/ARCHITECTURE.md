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

**In Phase 3**, OPA handles access control only (allow/deny the request). Instruction filtering uses SQL WHERE directly. OPA-driven filtering is added when policy complexity justifies it.

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

The meta-workflow is a hand-built collection of tools for the workflow lifecycle. It is the first real customer of the OPA pipeline — its instructions ("how to build workflows") are the first content in the instructions table.

**Human-in-the-loop by design.** The meta-workflow interviews the user on goals, proposes a decomposition into blocks, and iterates until the user approves. This HITL pattern must work across interfaces (kiro-cli chat now, web UI and Slack later).

### Capabilities

- **Interview**: Understand user goals — what problem the workflow solves, what triggers it, what it outputs. Propose blocks and pipeline structure. User approves/refines.
- **Research**: Proactively discover ideas and suggest use cases the user may not have thought of. Query knowledge base for similar workflows, patterns, and best practices.
- **Build**: Decompose into blocks → find existing blocks → create new if needed → compose reusable patterns (e.g., historical tracking) → wire pipeline → store instructions in DB → suggest triggers
- **Update**: "Kiro, help me update workflow X to do Y" → find existing instructions → modify/add/deprecate
- **Refine**: "Kiro, the instructions in workflow X step Y need better instructions" → targeted improvement of specific step instructions

### Reusable Patterns (Functional Composition)

The meta-workflow composes generic patterns into workflows. These are abstract, configurable capabilities — not workflow-specific logic.

**Historical Tracking** — for any workflow whose context drifts over time. Tracks where instructions came from and how they evolved. The specific strategy (version, migrate, deprecate, or combination) is configured per-workflow during the interview. Examples:
- repo-analysis: track convention changes so old code patterns are understood in context
- knowledge-ingest: track source versions so stale knowledge can be refreshed

More reusable patterns will emerge as workflows are built. The meta-workflow should identify when a new workflow needs a pattern that already exists and compose it in.

### How It Works

1. User requests a new workflow via kiro-cli (MCP/skill/agent discovery)
2. Meta-workflow interviews user on goals and use cases
3. Meta-workflow tools query OPA/pgvector for instructions about workflow building
4. Kiro proposes block decomposition, user approves/refines
5. Output: new instructions in DB + pipeline definition + thin trigger artifacts
6. End step: suggest trigger options (skill file, agent, MCP tool, future web UI/Slack) and promote trigger blocks so kiro-cli can discover them

### Trigger Blocks

The first block in a workflow — the entry point that kiro-cli or web UI executes. These get promoted to skills or agents so they're discoverable. The meta-workflow's end step handles this promotion.

### Why Hand-Built

The meta-workflow is the bootstrap — it can't build itself. It's the one workflow we code manually. Everything after it is produced BY it.

## Repo-Analysis (First Generated Workflow)

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

Blocks are typed functions, NOT Effect.Services. Services are for infrastructure (DB, OPA, Embedding). Blocks are domain logic that uses services.

Each block is a TypeScript module in `src/blocks/{name}.ts` exporting a `BlockDef` with metadata + an execute function that returns an Effect.

### Block Registry

Explicit registration at startup. Registry provides:
- List all blocks
- Search by capability (for meta-workflow reuse check)
- Get block by ID
- In-memory, populated from block modules at startup

### Block Executor

The generic execution engine that runs any block:
1. Takes block's `opa_context` declaration
2. Calls OPA with that context → gets filtering criteria
3. Runs core RAG loop (embed query → pgvector search with OPA filters → assemble context)
4. Injects retrieved instructions into block's execution context
5. Calls block's execute function with inputs + instructions
6. For blocks needing smart execution: routes to Kiro headless

This is the Phase 3 core loop applied per-block automatically.

### Pipeline Executor

Dynamic LangGraph StateGraph construction from pipeline definitions:
- Given a Pipeline definition, builds a StateGraph at runtime
- Each node = block execution via the block executor
- State flows via LangGraph state object, shaped by pipeline's `state_schema`
- PG checkpointer for persistent state across steps
- Current `Workflow.ts` gets refactored into this generic executor

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

### Phase 4a: Block Engine Infrastructure
- Block definition format (typed functions + metadata schema)
- Block registry (discover/list/search available blocks)
- Block executor (run block with inputs, inject OPA-scoped instructions, get outputs)
- Pipeline executor (dynamic LangGraph StateGraph from pipeline definitions)
- MCP stdio server wrapper for kiro-cli triggering
- Kiro headless service (Effect.Service wrapping headless API)
- Refactor Workflow.ts into generic pipeline executor

### Phase 4b: Meta-Workflow (Bootstrap)
- Hand-build the workflow lifecycle tools (interview, research, build, update, refine)
- First instructions in DB = "how to build workflows" (hand-written)
- Reusable patterns: historical tracking (generic, configurable per-workflow)
- End step: suggest triggers + generate SKILL.md + promote trigger blocks
- Validates the full OPA/LangGraph pipeline with real instructions
- Human-in-the-loop: interviews user, proposes decomposition, user approves

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
