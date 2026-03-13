# Kiro Cortex

Intelligent context management system for Kiro CLI, providing policy-governed semantic retrieval with pgvector and LangGraph.js orchestration.

## Overview

Kiro Cortex is a 4-layer architecture designed to manage millions of potential context items down to dozens of optimized, policy-compliant results for LLM consumption.

**Architecture Layers:**
1. **OPA (Policy Engine)** - Governance and compliance (millions → thousands)
2. **pgvector (Vector Store)** - Semantic retrieval (thousands → dozens)
3. **Context Engineering** - Query optimization and assembly (dozens → optimized)
4. **LangGraph.js (Orchestration)** - Agent workflow and state management

All components are open source, self-hosted, and managed via NixOS/Home Manager.

## Current Status

**Phase 1: COMPLETE** (2026-03-13)
- ✅ PostgreSQL with pgvector extension (port 5435)
- ✅ Effect-TS HttpApi server with database migrations
- ✅ OpenMemory SQLite → PostgreSQL migration (89 memories, 435 vectors)
- ✅ MCP operations validated (query, list, get, store, reinforce)
- ✅ Embedding search functional (nomic-embed-text, 768-dim vectors)

**Next Phase: Infrastructure Wiring (Phase 2)**
- Wire up OPA service and basic policy evaluation
- Integrate LangGraph.js orchestration layer
- Build end-to-end test pattern (query → OPA → pgvector → LangGraph)
- Validate full stack works before content migration

## Quick Start

### Prerequisites

- NixOS or Home Manager
- PostgreSQL 16+ with pgvector extension
- Ollama with nomic-embed-text model
- Node.js 20+ (via Nix)

### Setup

The system is configured via Home Manager in `home/caubut/features/cli/code/kiro/default.nix`:

```nix
# PostgreSQL service with pgvector
systemd.user.services.kiro-postgres = {
  # ... service configuration
};

# Environment variables for OpenMemory
OM_POSTGRES_HOST = "localhost";
OM_POSTGRES_PORT = "5435";
OM_POSTGRES_DB = "openmemory";
OM_TIER = "deep";  # 768-dim Ollama embeddings
```

Apply with:
```bash
home-manager switch
```

### Database Initialization

Database schema is initialized automatically via `ExecStartPost` in the systemd service:

```bash
kiro-cortex-db-init  # Runs migrations on service start
```

## Architecture

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for detailed design decisions, phase plan, and implementation notes.

## Development

**Tech Stack:**
- Effect-TS for type-safe functional programming
- effect-sql for database operations
- HttpApi for server layer
- pnpm for package management
- bun for runtime

**Key Files:**
- `src/index.ts` - HttpApi server entry point
- `src/Sql.ts` - Database schema and migrations
- `default.nix` (parent) - NixOS service configuration

**Run locally:**
```bash
pnpm install
bun run src/index.ts
```

## Migration Notes

### SQLite → PostgreSQL (Phase 1)

- **Data migrated:** 89 memories, 84 waypoints, 197 embed_logs, 9 temporal_facts
- **SQLite backup:** `~/.local/share/openmemory/memory.sqlite.bak`
- **Re-embedding:** 87 memories re-embedded (435 vectors = 87 × 5 sectors)
- **Empty content:** 2 memories (e0236682, d74388e4) have no vectors - harmless
- **Dimension fix:** Changed OM_TIER from "smart" (896-dim) to "deep" (768-dim) to match pgvector column

### Validation Results

- ✅ Row counts match across all 8 tables
- ✅ Content integrity verified (MD5 checks on 10 memories)
- ✅ Temporal facts preserved (9 facts, 4 with user_id)
- ✅ Vector search working (relevance scoring functional)
- ✅ MCP operations tested end-to-end

## User Preferences

- pnpm not npm, bun not node
- Effect-TS for all TypeScript code
- Pinned exact versions (no ^ or ~)
- All writes require user approval
- No one-off commands - declarative setup only (Nix or app-level migrations)
- Home Manager only (Ubuntu, not NixOS)

## License

MIT
