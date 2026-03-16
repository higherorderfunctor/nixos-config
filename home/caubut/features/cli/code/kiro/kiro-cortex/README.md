# Kiro Cortex

Workflow orchestration platform that solves context dilution. Instead of loading all steering files into every session, each workflow step gets only the rules relevant to that agent doing that task.

## Problem

Steering files don't scale. As repos, agents, and policies grow, context windows fill with irrelevant instructions. The LLM forgets or misapplies rules buried in noise.

## Solution

All codified knowledge (steering rules, coding standards, repo conventions, workflow definitions) stored as structured instructions with rich metadata. Hybrid orchestration: LangGraph for deterministic pipelines, Claude via MCP tool loops for AI-orchestrated workflows, and Kiro CLI subagents for autonomous block execution. Each step consults OPA for its specific rule set and retrieves relevant instructions via pgvector with precisely scoped context.

## Current Status

- Phase 0: Database Layer ✅
- Phase 1: Data Migration ✅
- Phase 2: Infrastructure Wiring ✅
- Phase 3: Core RAG Loop ✅
- Phase 4: MVP-Incremental Build
  - 4.1: Block Model + Registry ✅
  - 4.2: Pipeline Executor + HITL ✅
  - 4.3: MCP Stdio Wrapper ✅
  - 4.4: MVP Meta-Workflow ✅
  - Pre-4.5: OPA per-block injection ✅ (access.rego, scoping.rego, YAML loader, block executor)
  - 4.5+: Incremental features via meta-workflow itself
- Phase 5: Repo-Analysis (Built by Meta-Workflow)
- Phase 6: Web Dashboard (read-only)

## Quick Start

```bash
home-manager switch          # PostgreSQL + OPA services
cd kiro-cortex && pnpm install
# MCP server is launched by kiro-cli via mcp.json — not run directly
# For manual testing:
CORTEX_DEBUG=true bun src/mcp.ts
```

## Architecture

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for full design, phase plan, and rationale.

## Tech Stack

- Effect-TS + @effect/ai (MCP server, typed tools, layer composition)
- Bun runtime, pnpm package manager
- PostgreSQL 18 + pgvector (HNSW indexing)
- OPA with Rego v1 policies
- LangGraph.js (TypeScript) with PG checkpointer for deterministic pipelines
- Kiro CLI subagents for autonomous block execution, hooks for supplementary OPA
- Ollama for embeddings + classification
