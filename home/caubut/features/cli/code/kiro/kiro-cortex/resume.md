# kiro-cortex Resume — 2026-03-14

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via a hybrid model.

## Current State

Branch: chore/save-point, latest commit: b8147d0
Phase 4.5 meta-workflow blocks COMPLETE. 30 files, 0 errors (tsc + effect-language-service).

### What's Built (Phases 0-4.5 + conventions)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1 | done | Block model + BlockRegistry + migration 0003 |
| 4.2 | done | PipelineExecutor (dynamic StateGraph + PG checkpointer) |
| 4.3 | done | MCP stdio server + GET /workflows endpoint |
| 4.4 | done | MVP meta-workflow (route, interview, author, wire) + seed YAML |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports, co-located errors |
| 4.5 | done | decompose, research, optimize, promote blocks + audit/programmatic modes |

## File Structure

```
src/
  opa/{index,Opa}.ts           — OpaClient (Context.Tag), OpaApiError, layer
  embedding/{index,Embedding}.ts — EmbeddingClient (Context.Tag), EmbeddingApiError, layer, embed()
  instruction/{index,Repo,Loader,Error}.ts — InstructionRepo (Effect.Service), loadInstructions, layer
  workflow/{index,Block,Registry,Executor,Pipeline,Workflow}.ts — BlockRegistry, registryLayer
  meta-workflow/
    state.ts      — MetaWorkflowState (expanded: research, optimize, promote, programmatic fields)
    route.ts      — 5 modes: build, update, refine, audit, programmatic
    interview.ts  — HITL with research loop support + audit findings
    research.ts   — interrupt-based external knowledge gathering
    decompose.ts  — registry search, block proposal, programmatic validation
    optimize.ts   — rule-based bloat/spaghetti/DRY checks
    author.ts     — instruction YAML generation
    wire.ts       — pipeline YAML generation
    promote.ts    — SKILL.md + agent config generation
    graph.ts      — full StateGraph with loops
  Sql.ts, index.ts, mcp.ts, migrations/
```

## Meta-Workflow Graph (4.5)

```
BUILD/UPDATE: route → interview ↔ research → decompose → optimize → author → wire → promote → END
REFINE:       route → author → END
AUDIT:        route → optimize → interview → decompose → optimize → author → wire → promote → END
PROGRAMMATIC: route → decompose → optimize → author → wire → promote → END
```

## Dependencies (pinned exact)

effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.

## Memory References

- 3cfe2583 — session-8-complete (convention refactor)
- edbb7034 — session-6-final (hybrid arch)

## Next Steps (4.5+ remaining)

- isolation.rego — repo boundary enforcement (needed before Phase 5)
- Subagent integration — custom agent configs per workflow (UC-MW-20)
- Hooks integration — AgentSpawn + PreToolUse (UC-MW-23)
- AI-orchestrated block convention — structured output format (UC-MW-21)
- Phase 5: repo-analysis (built BY meta-workflow)
- Phase 6: Web dashboard + zod→Effect Schema exploration
