# Kiro Cortex Architecture

## Design Philosophy

Kiro Cortex addresses the fundamental challenge of LLM context management: how to intelligently select the most relevant information from millions of potential context items while maintaining policy compliance and governance.

The system uses a **funnel architecture** - each layer progressively filters and refines context:

```
Millions of items (all possible context)
    ↓ Layer 1: OPA Policy Engine
Thousands of items (policy-compliant)
    ↓ Layer 2: pgvector Semantic Retrieval
Dozens of items (semantically relevant)
    ↓ Layer 3: Context Engineering
Optimized context (ready for LLM)
    ↓ Layer 4: LangGraph.js Orchestration
Agent workflows with managed state
```

## Layer 1: OPA (Open Policy Agent)

**Purpose:** Governance and compliance enforcement

**Responsibilities:**
- IP protection (prevent proprietary data leakage)
- Data access control (user/workspace scoping)
- Compliance validation (regulatory requirements)
- Query sanitization before external tool use

**Technology:**
- OPA with Rego policy language
- Declarative policy rules
- Fast evaluation (sub-millisecond)

**Design Decisions:**
- **Why OPA?** Industry-standard policy engine, proven at scale, declarative rules
- **Why first layer?** Fail-fast on policy violations before expensive operations
- **Integration point:** All queries pass through OPA before reaching vector store

**Status:** Phase 2 (planned)

## Layer 2: pgvector (Vector Store)

**Purpose:** Semantic retrieval via embeddings

**Responsibilities:**
- Store 768-dimensional embeddings (nomic-embed-text via Ollama)
- Cosine similarity search with HNSW index
- Multi-sector storage (episodic, semantic, procedural, emotional, reflective)
- Temporal fact graph for time-aware queries

**Technology:**
- PostgreSQL 16+ with pgvector extension
- HNSW index for fast approximate nearest neighbor search
- Effect-TS for type-safe database operations

**Design Decisions:**
- **Why PostgreSQL?** Self-hosted, mature, excellent Nix support, ACID guarantees
- **Why pgvector?** Native PostgreSQL extension, no separate vector DB to manage
- **Why 768-dim?** Matches nomic-embed-text output, good balance of quality/performance
- **Why HNSW?** Fast approximate search, configurable accuracy/speed tradeoff
- **Port 5435:** Avoids conflicts with system PostgreSQL (default 5432)

**Schema:**
- `openmemory_memories` - Core memory content
- `openmemory_vectors` - 768-dim embeddings with sector classification
- `openmemory_waypoints` - Hierarchical memory organization
- `temporal_facts` - Subject-predicate-object triples with validity periods
- `temporal_edges` - Fact relationships

**Status:** Phase 1 COMPLETE (2026-03-13)

## Layer 3: Context Engineering

**Purpose:** Query optimization and context assembly

**Responsibilities:**
- Query expansion and refinement
- Retrieval strategy selection (semantic, temporal, hybrid)
- Context window management (token budget optimization)
- Result ranking and deduplication
- Context assembly for LLM consumption

**Technology:**
- Effect-TS for composable query pipelines
- Custom retrieval strategies
- Token counting and budget management

**Design Decisions:**
- **Why separate layer?** Decouples retrieval from orchestration, enables A/B testing of strategies
- **Why Effect-TS?** Type-safe composition, error handling, testability
- **Retrieval strategies:**
  - Semantic: Pure vector similarity
  - Temporal: Time-aware fact queries
  - Hybrid: Combine semantic + temporal + recency signals

**Status:** Phase 3 (planned)

## Layer 4: LangGraph.js (Orchestration)

**Purpose:** Agent workflow orchestration and state management

**Responsibilities:**
- Multi-agent workflow coordination
- State persistence across interactions
- Tool integration and routing
- Conditional branching based on context
- Human-in-the-loop checkpoints

**Technology:**
- LangGraph.js (TypeScript port of LangGraph)
- Effect-TS for state management
- Graph-based workflow definition

**Design Decisions:**
- **Why LangGraph?** Proven pattern for agent orchestration, graph topology for complex workflows
- **Why not Kiro's native subagents?** LangGraph provides state persistence, conditional routing, and workflow visualization
- **Integration:** LangGraph calls Context Engineering layer for retrieval, OPA for policy checks

**Status:** Phase 4 (planned)

## Phased Implementation Plan

### Phase 0: Database Layer ✅ COMPLETE (commit 75d246a)

**Goal:** Establish PostgreSQL + pgvector foundation

**Deliverables:**
- PostgreSQL service with pgvector extension (port 5435)
- Effect-TS HttpApi server
- Database migrations with effect-sql
- Schema: memories, vectors, waypoints, temporal_facts, stats, users

**Time:** ~8 hours

### Phase 1: Data Migration ✅ COMPLETE (commit 33f656f, 2026-03-13)

**Goal:** Migrate OpenMemory from SQLite to PostgreSQL

**Deliverables:**
- Data migration script (89 memories, 84 waypoints, 197 embed_logs, 9 temporal_facts)
- Re-embedding with nomic-embed-text (435 vectors = 87 memories × 5 sectors)
- MCP validation (query, list, get, store, reinforce)
- Embedding dimension fix (OM_TIER: smart → deep)

**Key Decisions:**
- **OM_TIER=deep:** Pure Ollama 768-dim embeddings (not smart's 896-dim fusion)
- **SQLite backup:** Preserved at `~/.local/share/openmemory/memory.sqlite.bak`
- **Empty content handling:** 2 memories (e0236682, d74388e4) have no vectors - acceptable

**Validation:**
- ✅ Row counts match across all 8 tables
- ✅ Content integrity (MD5 checks on 10 memories)
- ✅ Temporal facts preserved (9 facts, 4 with user_id)
- ✅ Vector search functional (relevance scoring works)
- ✅ MCP operations tested end-to-end

**Time:** ~12 hours

### Phase 2: Infrastructure Wiring (NEXT)

**Goal:** Wire up full stack (OPA + LangGraph) with minimal test policies

**Deliverables:**
- OPA service in Nix configuration
- Minimal test policy (allow/deny pattern)
- LangGraph.js service setup
- End-to-end test: query → OPA → pgvector → Context Engineering → LangGraph
- Validate full stack integration

**Key Decisions:**
- **Infrastructure first:** Get all layers communicating before migrating steering content
- **Minimal policies:** Simple allow/deny rules for testing, not production IP protection yet
- **Test pattern:** Single workflow that exercises all 4 layers
- **Defer content migration:** Steering files → OPA policies happens in Phase 4

**Estimated Time:** ~6 hours

### Phase 3: Context Engineering (PLANNED)

**Goal:** Implement retrieval strategies and context optimization

**Deliverables:**
- Semantic retrieval strategy
- Temporal retrieval strategy
- Hybrid retrieval (semantic + temporal + recency)
- Token budget management
- Context assembly pipeline

**Key Decisions:**
- Strategy selection: Automatic based on query type
- Token counting: Use tiktoken for accurate counts
- Ranking: Combine similarity score + salience + recency

**Estimated Time:** ~10 hours

### Phase 4: Content Migration & Enhancement (PLANNED)

**Goal:** Migrate steering files to OPA policies and add production features

**Deliverables:**
- Convert IP protection steering (00-ip-protection.md) to Rego policies
- User/workspace scoping policies
- Query sanitization policies
- Policy violation logging
- Steering file migration guide
- Production-ready policy test suite

**Key Decisions:**
- Steering → Rego mapping strategy
- Policy versioning approach
- Rollback mechanism for policy changes
- Policy testing framework

**Estimated Time:** ~12 hours

### Phase 5: LangGraph Workflows (PLANNED)

**Goal:** Define production workflows for common agent patterns

**Deliverables:**
- Research workflow (Tier 3 from steering)
- Multi-step analysis workflow
- Human-in-the-loop checkpoints
- State persistence patterns
- Workflow visualization

**Key Decisions:**
- State storage: PostgreSQL (reuse existing DB)
- Workflow definition: TypeScript (type-safe)
- Integration: LangGraph calls Context Engineering layer

**Estimated Time:** ~10 hours

**Total Estimated Time:** 58 hours (revised from 50 hours)

## Design Rationale

### Why 4 Layers?

**Separation of Concerns:**
- Policy (Layer 1) is independent of retrieval (Layer 2)
- Retrieval (Layer 2) is independent of optimization (Layer 3)
- Optimization (Layer 3) is independent of orchestration (Layer 4)

**Testability:**
- Each layer can be tested in isolation
- Mock interfaces between layers
- Unit test policies, retrieval strategies, context assembly separately

**Flexibility:**
- Swap vector stores (pgvector → Qdrant) without changing other layers
- A/B test retrieval strategies without touching orchestration
- Update policies without redeploying services

### Why Self-Hosted?

**Control:**
- No vendor lock-in
- Full data ownership
- Custom optimizations

**Cost:**
- No per-query API fees
- Predictable infrastructure costs
- Scale on own hardware

**Privacy:**
- Proprietary data never leaves infrastructure
- Compliance-friendly (GDPR, HIPAA, etc.)
- Audit trail under full control

### Why Effect-TS?

**Type Safety:**
- Compile-time guarantees for database operations
- Effect types encode success/failure modes
- Composable error handling

**Testability:**
- Pure functions, no hidden side effects
- Dependency injection via Effect layers
- Mock services for testing

**Performance:**
- Lazy evaluation
- Efficient resource management
- Structured concurrency

## Migration Notes

### SQLite → PostgreSQL (Phase 1)

**Challenges:**
1. **Embedding dimensions:** SQLite had mixed 768-dim and null vectors, PG schema enforced vector(768)
2. **Re-embedding required:** OpenMemory doesn't auto-re-embed null vectors
3. **OM_TIER mismatch:** "smart" tier produces 896-dim vectors (768 Ollama + 128 synthetic fusion)

**Solutions:**
1. Created reembed_memories.py script to re-embed 87 memories
2. Changed OM_TIER from "smart" to "deep" (pure Ollama 768-dim)
3. Validated nomic-embed-text is correct model (768-dim output)

**Results:**
- 89 memories migrated (87 with vectors, 2 empty content)
- 435 vectors created (87 memories × 5 sectors)
- All MCP operations validated
- SQLite backup preserved for rollback

### Table Mapping

| SQLite Table | PostgreSQL Table | Notes |
|--------------|------------------|-------|
| memories | openmemory_memories | Added `openmemory_` prefix |
| vectors | openmemory_vectors | Changed to vector(768) type |
| waypoints | openmemory_waypoints | Hierarchical organization |
| embed_logs | openmemory_embed_logs | Embedding operation history |
| temporal_facts | temporal_facts | No prefix (shared namespace) |
| temporal_edges | temporal_edges | Fact relationships |
| stats | stats | System statistics |
| users | openmemory_users | User management |

## Future Considerations

### Scaling

**Current:** Single PostgreSQL instance, HNSW index
**Future:** 
- Read replicas for query load
- Partitioning by user_id or workspace
- Separate hot/cold storage (recent vs archived memories)

### Observability

**Current:** Basic logging
**Future:**
- Query latency metrics
- Policy evaluation timing
- Retrieval strategy effectiveness
- Context window utilization

### Advanced Features

**Potential additions:**
- Multi-modal embeddings (text + code + images)
- Cross-workspace knowledge sharing (with policy controls)
- Automatic memory consolidation (merge similar memories)
- Proactive context suggestions (anticipate user needs)

## References

- [OpenMemory MCP](https://github.com/caubut/openmemory-mcp) - Memory management protocol
- [pgvector](https://github.com/pgvector/pgvector) - PostgreSQL vector extension
- [OPA](https://www.openpolicyagent.org/) - Open Policy Agent
- [LangGraph](https://github.com/langchain-ai/langgraph) - Agent orchestration framework
- [Effect-TS](https://effect.website/) - Functional TypeScript framework
