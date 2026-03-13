# Kiro Cortex Architecture

## Problem

Steering files don't scale. As repos, agents, and policies grow, context windows fill with irrelevant instructions. The LLM forgets or misapplies rules buried in noise.

## Vision

kiro-cortex is a **workflow orchestration platform** that solves context dilution. Instead of dumping all instructions into context, each workflow step gets only the rules relevant to THAT agent doing THAT task.

All codified knowledge — steering rules, coding standards, repo conventions, workflow definitions, skill definitions, MCP usage patterns — stored as structured instructions. LangGraph orchestrates multi-step workflows where each step consults OPA for its specific rule set.

## Architecture

```
Triggers: kiro-cli (MCP/skills) | Web UI (future) | Slack (future)
    │
    ▼
┌─ kiro-cortex (LangGraph Orchestration) ──────────────────────┐
│                                                               │
│  Workflow Step 1:                                             │
│    OPA: "agent=X, task=analyze, domain=Y"                     │
│    → returns relevant instruction IDs                         │
│    pgvector: semantic search within allowed set                │
│    → top N instructions by relevance                          │
│    Assemble: fit to token budget                              │
│    → Kiro headless executes with scoped context               │
│                                                               │
│  Workflow Step 2:                                             │
│    OPA: different agent/task → different rules                │
│    → ... same pattern, different context                      │
│                                                               │
│  Persistent state across steps (PG checkpointer)              │
└───────────────────────────────────────────────────────────────┘

┌─ INSTRUCTION DATA LAYER ─────────────────────────────────────┐
│  PostgreSQL: instruction metadata + embeddings (single DB)    │
│  All codified knowledge: steering rules, coding standards,    │
│  repo conventions, workflow defs, skill defs, MCP patterns    │
│  Rich metadata for OPA filtering                              │
└───────────────────────────────────────────────────────────────┘

┌─ OPA (Policy Engine) ────────────────────────────────────────┐
│  Rego policies filter instructions by:                        │
│  agent role, task type, domain, tier, permissions             │
│  Consulted PER WORKFLOW STEP, not once per query              │
│  Conflict resolution, IP protection                           │
└───────────────────────────────────────────────────────────────┘
```

## LLM Roles

| LLM | Role | When |
|-----|------|------|
| Kiro (Claude, headless/API) | Complex reasoning, tool use, code generation | Workflow steps that need smart execution |
| Ollama (nomic-embed-text) | Embeddings for vector search | Every query — turning text into vectors |
| Ollama (llama3.2 etc) | Classification, tagging of bulk data | Preprocessing before Kiro — simple/cheap tasks |

Kiro is always the smart executor. Ollama handles embeddings and bulk classification. No Ollama for generation in workflows.

## Trigger Surfaces

**kiro-cli (MCP):**
- MCP server exposes `list_workflows`, `run_workflow` tools
- kiro-cli discovers available workflows, user triggers them in chat
- For common workflows: generate SKILL.md files to help steer kiro-cli toward using them
- MCP is a thin stdio wrapper → HTTP calls to kiro-cortex

**Web UI (future):**
- Direct HTTP to kiro-cortex API
- LangGraph Studio for workflow visualization
- Trigger and monitor workflows

**Slack (future):**
- Webhook → kiro-cortex API
- Trigger workflows from Slack messages

All triggers share the same HTTP API, same pipeline, same state.

## Execution Modes

The pipeline is identical regardless of trigger. What differs is what happens after context assembly:

- **MCP trigger** (kiro-cli): Return assembled context + metadata. kiro-cli injects into Claude's prompt. Workflow stops after assembly.
- **Direct trigger** (web/Slack): No external LLM in the loop. LangGraph routes to Kiro headless for execution. Returns complete response.

Context size is configurable per-call. The trigger specifies a token budget based on task complexity (e.g., simple question → 2000 tokens, complex debugging → 8000).

## DB Split Strategy

Single PostgreSQL instance now. Instruction metadata and embeddings share the same DB (`kiro_cortex`). When scaling demands it, split is mechanical:

- Put instruction access behind its own Effect Service (`InstructionRepo`)
- Currently provided with the shared `SqlLive` layer
- To split: provide with a separate `VectorSqlLive` pointing to a dedicated DB
- Service interface unchanged, callers unaffected — one layer swap

## Instruction Metadata Schema

Each piece of codified knowledge becomes a structured instruction:

```json
{
  "instruction_id": "project-a-effect-patterns-001",
  "text": "Use Effect.gen for all effectful pipelines...",
  "source": "steering/coding-standards/effect-patterns.md",
  "domain": "coding-standards",
  "subdomain": "effect-patterns",
  "repo": "org/project-a",
  "tier_access": [1, 2],
  "agent_roles": ["developer", "reviewer"],
  "task_types": ["coding", "review", "debugging"],
  "priority": "high",
  "version": "1.0",
  "effective_date": "2026-03-08",
  "expiry_date": null,
  "dependencies": [],
  "conflict_group": "effect-style",
  "embedding": [0.023, -0.118, ...]
}
```

Maps directly to existing steering structure:
- `policies/` → domain="policy", agent_roles=["all"]
- `<agent-context>/<domain>/` → domain="<domain>", agent_roles=["developer"]
- `~/.kiro/steering/*.md` → domain="global", task_types=["all"]

## Key Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Platform role | Workflow orchestration (not just context prep) | Each step needs different rules, not one-shot context |
| Smart executor | Kiro headless (not Ollama) | Kiro has tools, reasoning, quality |
| Ollama role | Embeddings + classification only | Cheap/fast for bulk preprocessing |
| OPA consultation | Per workflow step | Different steps need different rule sets |
| Single DB | PostgreSQL (metadata + vectors together) | Split to separate instances when scaling demands it |
| Trigger discovery | MCP tools + generated skills | Discoverable by default, skills for steering if needed |
| Vector index | HNSW over IVFFlat | Better accuracy, configurable speed tradeoff |
| Hosting | Self-hosted, NixOS/Home Manager | Full control, privacy, no vendor lock-in |
| Embeddings | nomic-embed-text 768-dim (Ollama) | Local, no API costs |
| Runtime | Bun + pnpm, Effect-TS | User preference, type safety |
| Token estimation | chars/4 approximation | Upgrade to tiktoken when accuracy matters |
| Context budget | Caller-specified per request | Task complexity determines budget |
| DB split strategy | Effect Service boundary (InstructionRepo) | Layer swap when scaling demands it |

## Phase Plan

### Phase 0: Database Layer ✅ (commit 75d246a)
- PostgreSQL 18 + pgvector on port 5435
- Effect-TS HttpApi server with migrations
- Schema: memories, vectors, waypoints, temporal_facts, stats, users

### Phase 1: Data Migration ✅ (commit 33f656f)
- OpenMemory SQLite → PostgreSQL (89 memories, 435 vectors)
- OM_TIER: smart (896-dim) → deep (768-dim pure Ollama)
- MCP operations validated end-to-end

### Phase 2: Infrastructure Wiring ✅ (commit ab33b12)
- OPA systemd service (port 8181, out-of-store symlink to policies)
- OpaService: Effect.Service + NodeHttpClient.layer + tagged OpaError
- LangGraph StateGraph: policy → vector → assemble → generate nodes
- HttpApi /test endpoint wiring all layers
- Tagged errors (TestError, OpaError) registered on endpoint schemas

### Phase 3: Instruction Data Layer + Retrieval (NEXT)
- Instruction metadata schema (PostgreSQL migration)
- Test seed data (hand-written instructions, not migrated steering)
- Real vector retrieval (embed query via Ollama, HNSW search)
- Real OPA pre-filtering (Rego policies on instruction metadata)
- Context assembly with token budgets
- `/context` endpoint for testing the pipeline with curl

### Phase 4: Content Migration
- Convert steering files → structured instructions
- Ingestion pipeline (parse markdown → extract rules → tag metadata → embed)
- Production OPA policies
- Conflict detection/resolution in Rego

### Phase 5: Workflow Engine
- Production workflow definitions (analysis, debugging, research)
- Per-step OPA consultation pattern
- Kiro headless integration
- PostgreSQL checkpointer for persistent state
- Conditional routing (MCP → return context, web/slack → full execution)

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
