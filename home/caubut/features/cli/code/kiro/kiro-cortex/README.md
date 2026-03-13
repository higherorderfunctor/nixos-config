# Kiro Cortex

Intelligent context management system for Kiro CLI. Scales millions of instructions down to optimally dense context windows via policy-governed semantic retrieval and LangGraph.js orchestration.

## Overview

Kiro Cortex solves context dilution: when you have millions of instructions/rules/policies, you can't shove them all into an LLM's context window. The system uses a funnel architecture where each layer progressively filters:

1. **OPA (Policy Engine)** — Millions → Thousands (deterministic Rego filtering by role, tier, domain)
2. **pgvector (Semantic Retrieval)** — Thousands → Dozens (HNSW vector similarity + hybrid search)
3. **Context Engineering** — Dozens → Optimized (compression, windowing, memory tiers)
4. **LangGraph.js (Orchestration)** — Workflow graphs with persistent state, multi-trigger entry

All open source, self-hosted, managed via Home Manager (Ubuntu).

## Triggers

Workflows can be triggered from multiple surfaces:
- **kiro-cli** — Chat-based invocation via MCP
- **Web UI** — Future thin React UI or LangGraph Studio
- **Slack bot** — Future webhook-triggered workflows

## Current Status

- Phase 0: Database Layer ✅ (PostgreSQL + pgvector, port 5435)
- Phase 1: Data Migration ✅ (OpenMemory SQLite → PG, 89 memories, 435 vectors)
- Phase 2: Infrastructure Wiring ✅ (OPA + LangGraph + HttpApi end-to-end)
- Phase 3: Context Engineering — NEXT
- Phase 4: Content Migration — Steering files → OPA policies + instruction metadata

## Quick Start

```bash
# Apply Nix config (PostgreSQL + OPA services)
home-manager switch

# Install dependencies
cd kiro-cortex && pnpm install

# Start server
bun run src/index.ts

# Test
curl http://localhost:3100/health
curl -X POST http://localhost:3100/test \
  -H 'Content-Type: application/json' \
  -d '{"query":"hello","user_id":"test"}'
```

## Architecture

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for full design, phase plan, and rationale.

## Tech Stack

- Effect-TS + HttpApi (server, typed errors, layer composition)
- Bun runtime, pnpm package manager
- PostgreSQL 18 + pgvector (HNSW indexing)
- OPA with Rego v1 policies
- LangGraph.js (TypeScript) with PG checkpointer
- @effect/platform-node for HTTP client (NodeHttpClient.layer)

## Key Files

- `src/index.ts` — HttpApi server (/health, /test endpoints)
- `src/Opa.ts` — OPA client service (Effect.Service + NodeHttpClient)
- `src/Workflow.ts` — LangGraph StateGraph test workflow
- `src/Sql.ts` — Database layer (effect-sql migrations)
- `src/KiroContextError.ts` — Tagged error schemas
- `policies/test.rego` — Rego v1 test policy

## User Preferences

- pnpm not npm, bun not node, Effect-TS for all TypeScript
- Pinned exact versions (no ^ or ~), renovate for updates
- All writes require user approval
- Declarative setup only (Nix or app-level migrations)
- Home Manager only (Ubuntu, not NixOS)
