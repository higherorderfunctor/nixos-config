# Kiro Cortex

Workflow orchestration platform that solves context dilution. Instead of loading all steering files into every session, each workflow step gets only the rules relevant to that agent doing that task.

## Problem

Steering files don't scale. As repos, agents, and policies grow, context windows fill with irrelevant instructions. The LLM forgets or misapplies rules buried in noise.

## Solution

All codified knowledge (steering rules, coding standards, repo conventions, workflow definitions) stored as structured instructions with rich metadata. LangGraph orchestrates multi-step workflows where each step consults OPA for its specific rule set, retrieves relevant instructions via pgvector, and invokes Kiro (headless) with precisely scoped context.

## Current Status

- Phase 0: Database Layer ✅
- Phase 1: Data Migration ✅
- Phase 2: Infrastructure Wiring ✅
- Phase 3: Core RAG Loop ✅
- Phase 4a: Block Engine Infrastructure — NEXT
- Phase 4b: Meta-Workflow (Bootstrap)
- Phase 5: Repo-Analysis (Built by Meta-Workflow)
- Phase 6: Web UI

## Quick Start

```bash
home-manager switch          # PostgreSQL + OPA services
cd kiro-cortex && pnpm install
bun run src/index.ts         # Start server on port 3100

curl http://localhost:3100/health
curl -X POST http://localhost:3100/context \
  -H 'Content-Type: application/json' \
  -d '{"query":"how should I write Effect code","user_id":"caubut"}'
```

## Architecture

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for full design, phase plan, and rationale.

## Tech Stack

- Effect-TS + HttpApi (server, typed errors, layer composition)
- Bun runtime, pnpm package manager
- PostgreSQL 18 + pgvector (HNSW indexing)
- OPA with Rego v1 policies
- LangGraph.js (TypeScript) with PG checkpointer
- Kiro headless for smart execution, Ollama for embeddings + classification
