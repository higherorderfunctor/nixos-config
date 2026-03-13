# Kiro Cortex Architecture

## Vision

Scale to millions of instructions across tiered multi-agent workflows. Solve context dilution by filtering millions down to an optimally dense context window per agent execution. Triggerable from kiro-cli, web, or Slack.

## Funnel Architecture

```
Triggers: kiro-cli (MCP) | Web UI | Slack bot
    │
    ▼
┌─ ORCHESTRATION (LangGraph.js) ──────────────┐
│  Workflow graphs, persistent state (PG),      │
│  agent lifecycle, handoffs, conditional routing│
│  Human-in-the-loop checkpoints                │
└──────────────┬───────────────────────────────┘
               ▼
┌─ OPA GOVERNANCE ─────────────────────────────┐
│  Rego policies filter by: agent role, tier,   │
│  domain, task type, permissions, compliance   │
│  Conflict resolution, IP protection           │
│  Millions → Thousands                         │
└──────────────┬───────────────────────────────┘
               ▼
┌─ SEMANTIC RETRIEVAL (pgvector) ──────────────┐
│  HNSW indexing, hybrid search (dense+sparse)  │
│  Task-aware instruction embeddings            │
│  Two-database isolation for queries           │
│  Thousands → Dozens                           │
└──────────────┬───────────────────────────────┘
               ▼
┌─ CONTEXT ENGINEERING ────────────────────────┐
│  Compression, summarization, windowing        │
│  Memory tiers: working / short-term / long    │
│  Token budget management                      │
│  Dozens → Optimized context                   │
└──────────────┬───────────────────────────────┘
               ▼
┌─ AGENT EXECUTION ────────────────────────────┐
│  Receives precise, minimal, relevant context  │
└──────────────────────────────────────────────┘

┌─ INSTRUCTION DATA LAYER ─────────────────────┐
│  Metadata DB + Vector DB (two DBs, isolated)  │
│  Versioning, ingestion pipeline, auto-tagging │
│  Feeds both OPA (metadata) and pgvector       │
└──────────────────────────────────────────────┘
```

## Instruction Metadata Schema

Each instruction needs rich metadata for OPA filtering:

```json
{
  "instruction_id": "fin-compliance-2847",
  "text": "When processing wire transfers over $10,000...",
  "domain": "finance",
  "subdomain": "compliance",
  "tier_access": [1, 2],
  "agent_roles": ["compliance_reviewer"],
  "task_types": ["wire_transfer", "aml_screening"],
  "priority": "critical",
  "version": "3.2",
  "effective_date": "2025-01-15",
  "expiry_date": null,
  "dependencies": ["fin-compliance-2201"],
  "conflict_group": "wire_transfer_rules",
  "embedding_vector": [0.023, -0.118, ...]
}
```

## Key Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Language | TypeScript (Effect-TS) | User preference, type safety, Bun runtime |
| Vector index | HNSW over IVFFlat | Better accuracy, configurable speed tradeoff |
| DB isolation | Two separate databases | Query isolation, independent scaling |
| Policy engine | OPA + Rego v1 | Industry standard, sub-ms evaluation, CNCF graduated |
| Orchestration | LangGraph.js | Persistent state, graph workflows, multi-agent, TS native |
| Triggers | Multi-surface | kiro-cli (MCP), web UI, Slack bot |
| Hosting | Self-hosted, NixOS/HM | Full control, no vendor lock-in, privacy |
| Embeddings | nomic-embed-text 768-dim | Local Ollama, no API costs |
| Runtime | Bun + pnpm | Fast, user preference |

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
- Layer composition: HttpApiBuilder.api(Api).pipe(Layer.provide(groups))

### Phase 3: Context Engineering (NEXT)
- Retrieval strategies (semantic, temporal, hybrid)
- Token budget management
- Context assembly pipeline
- Instruction data layer (metadata schema, versioning, ingestion)

### Phase 4: Content Migration
- Steering files → OPA Rego policies
- Instruction metadata population
- Production policy test suite
- Conflict detection/resolution in Rego

### Phase 5: LangGraph Workflows
- Production workflow definitions
- PostgreSQL checkpointer for persistent state
- Multi-trigger support (web, Slack)
- Human-in-the-loop checkpoints

### Phase 6: UI (LAST)
- LangGraph Studio for workflow visualization
- OPA policy management
- Knowledge graph visualization (if needed)

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
