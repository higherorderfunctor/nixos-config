# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5 meta-workflow blocks COMPLETE. 30 files, 0 errors.
Items 1-2 of 4.5+ done. Items 3+4 merged. Q1 resolved, Q2 open.

### Commits This Session
| SHA | What |
|-----|------|
| `99505e2` | Fix audit mode graph routing + docs gaps |
| `266aea0` | BlockOutput type for AI-orchestrated blocks (UC-MW-21) |
| `bca7337` | isolation.rego + wire repo into block executor |
| `71684a2` | Use case updates (UC-MW-20,22,23,24,25) |
| (pending) | Segment model + Q1 resolution |

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ item 1 | done | BlockOutput type (UC-MW-21) |
| 4.5+ item 2 | done | isolation.rego + repo param in executeBlock |

## Segment Model (Q1 Resolved)

**Decision:** Single `run_workflow` MCP tool with interrupt/resume. No separate `run_block` tool.

A workflow = sequence of deterministic LangGraph segments. Between segments, Claude takes over (Sequential Thinking pattern). `run_workflow` runs until an AI boundary (`interrupt()`), returns `BlockOutput`, Claude does its work (reason, ask user, spawn subagent), calls `run_workflow` with same `thread_id` to resume.

**Pattern variants are segment configurations:**
- Pure deterministic = 1 segment, no interrupts (run_workflow runs end-to-end)
- Hybrid = N segments with AI boundaries (most real workflows)
- Pure AI-orchestrated = N single-block segments with boundaries between all (rare)

**Reusable segments (UC-MW-18):** LangGraph sub-graphs in `src/shared/`. Compose into any workflow as nodes. `run_workflow` traverses them transparently including internal interrupt points. Parameterizable via state. Optimize block recommends extracting DRY violations into shared segments.

## 4.5+ Remaining: Subagent + Hooks Integration

### Open question:
- Q2: How does BlockOutput.next_step encode "spawn subagent X with task Y"? Structured discriminated union or free text?

### What to implement (after Q2 resolved):
- Update BlockOutput type with structured next_step (per Q2 answer)
- Enhance promote block's agent config generation (hooks, subagent settings, mcpServers)
- Create shared hook script conventions
- Document BlockOutput → Claude → use_subagent convention

### Use cases (in ARCHITECTURE.md):
- UC-MW-20: Agent configs include hooks, toolsSettings.subagent, mcpServers, resources, prompt
- UC-MW-22: Mechanism: BlockOutput.next_step → Claude → use_subagent
- UC-MW-23: Hooks per-agent in config; scripts reusable in ~/.kiro/hooks/
- UC-MW-24: Single run_workflow tool, interrupt/resume at AI boundaries, no run_block
- UC-MW-25: Meta-workflow proposes hooks (workflow-specific or reusable)

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

## Key References
- Subagent tool limitations: https://kiro.dev/docs/cli/chat/subagents/#tool-availability
- Agent config format: hooks, toolsSettings.subagent, mcpServers, resources (from Kiro docs)
- Segment model: ARCHITECTURE.md "Segment Model" section under orchestration

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
