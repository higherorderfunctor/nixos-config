# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. 30 files, 0 errors.
All design questions resolved. All implementation items done.

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ | done | Segment model, NextStep union, UC-MW-26/27/28, hook conventions, artifact templates |

## Design Decisions (All Resolved)

- Q1: Segment model — single `run_workflow` with interrupt/resume, no run_block
- Q2: NextStep discriminated union — resume, spawn_subagent, ask_user, complete
- UC-MW-26: Interview asks trigger type → promote generates skill OR agent config
- UC-MW-27: Meta-workflow is top-level agent (`~/.kiro/agents/meta-workflow.json`, Ctrl+Shift+M)
- UC-MW-28: Context optimization — skills > agents > subagents > MCPs

## Next: Phase 5 — Repo-Analysis

First workflow built by meta-workflow:
- Git worktree aware (repo identity by remote origin)
- Instruction scoping (repo-specific vs framework-agnostic, OPA enforced)
- Historical tracking pattern for convention evolution
- Knowledge seeding (detect frameworks → suggest sources → HITL → ingest)
- Known sources: EffectPatterns (300+), effect-solutions (10+)

## File Structure

```
src/
  opa/{index,Opa}.ts
  embedding/{index,Embedding}.ts
  instruction/{index,Repo,Loader,Error}.ts
  workflow/{index,Block,Registry,Executor,Pipeline,Workflow}.ts
  meta-workflow/{state,route,interview,research,decompose,optimize,author,wire,promote,graph}.ts
  Sql.ts, index.ts, mcp.ts, migrations/
policies/access.rego, scoping.rego, isolation.rego
```

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
