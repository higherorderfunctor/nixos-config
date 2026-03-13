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

### Layer 2: Policy Governance (Phase 5)

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

**In Phase 3**, OPA handles access control only (allow/deny the request). Instruction filtering uses SQL WHERE directly. OPA-driven filtering is added in Phase 5 when policy complexity justifies it.

### Layer 3: Workflow Orchestration (Phase 5)

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

## How Instructions Get Into the Table

**Phase 3 (now):** Hand-written test seed data. 5-10 instructions inserted via SQL migration with pre-computed embeddings. Validates the retrieval pipeline without building an ingestion system.

**Phase 4 (later):** Ingestion pipeline.
```
  Steering file (markdown)
    → parse into individual rules/conventions
    → tag with metadata (domain, agent_roles, task_types, priority, ...)
    → embed text via Ollama (nomic-embed-text, 768-dim)
    → INSERT into instructions table
```

This is a batch process, not real-time. Run it when steering files change. Ollama handles classification/tagging for bulk data (cheap, fast, local).

## Execution Modes

The pipeline is identical regardless of trigger. What differs is what happens after context assembly:

- **MCP trigger** (kiro-cli): Return assembled context + metadata. kiro-cli injects into Claude's prompt. Workflow stops after assembly.
- **Direct trigger** (web/Slack, future): LangGraph routes to Kiro headless for full execution. Returns complete response.

Context size is configurable per-call via `token_budget` parameter.

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
- LangGraph StateGraph with stub nodes (policy → vector → assemble → generate)
- HttpApi /test endpoint wiring OPA + LangGraph end-to-end

### Phase 3: Core RAG Loop (NEXT)
Build the core retrieval pipeline with real data:
- Add missing columns to instructions table (source, repo, effective_date, expiry_date)
- EmbeddingService: Effect Service wrapping Ollama /api/embed
- InstructionRepo: Effect Service for instruction search (the future DB-split boundary)
- Test seed data: 5-10 hand-written instructions with real embeddings
- Wire workflow nodes to real services (replace stubs)
- OPA for access control only (allow/deny) — SQL WHERE for instruction filtering
- Context assembly with token budgets (chars/4)
- `/context` endpoint replacing `/test`

### Phase 4: Content Migration
- Ingestion pipeline: parse steering markdown → extract rules → tag metadata → embed → insert
- Bulk classification via Ollama (domain, task_type tagging)
- Production seed data from real steering files

### Phase 5: Workflow Engine + Policy Layer
- OPA-driven instruction filtering (Rego policies generate SQL WHERE criteria)
- Per-step OPA consultation pattern
- Production workflow definitions (analysis, debugging, research)
- Kiro headless integration
- PostgreSQL checkpointer for persistent workflow state
- Conditional routing (MCP → return context, web/slack → full execution)
- Conflict detection/resolution in Rego

### Phase 6: Triggers + Discovery
- MCP stdio wrapper for kiro-cli
- Register in default.nix mcp.json
- Generated SKILL.md files for common workflows
- Web UI (LangGraph Studio or custom)

## Effect-TS Patterns

Established patterns from Phase 2:

- `Effect.Service` with `dependencies` array for layer provision
- `NodeHttpClient.layer` in dependencies (self-contained, no agent leak)
- `Schema.TaggedError` for API errors, registered via `.addError()` on endpoints
- `HttpApiBuilder.api(Api).pipe(Layer.provide(groups))` — api needs groups, not reverse
- `HttpLive.pipe(Layer.launch, BunRuntime.runMain)` for server startup
- `effect-language-service diagnostics --project tsconfig.json` for Effect-specific checks

## References

- [OPA](https://www.openpolicyagent.org/) — Open Policy Agent
- [LangGraph.js](https://langchain-ai.github.io/langgraphjs/) — Agent orchestration
- [pgvector](https://github.com/pgvector/pgvector) — PostgreSQL vector extension
- [Effect-TS](https://effect.website/) — Functional TypeScript framework
