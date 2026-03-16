# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via a hybrid model (LangGraph deterministic + Claude AI-orchestrated + Kiro subagents).

## Current State

Branch: chore/save-point
Phase 4.5 meta-workflow blocks COMPLETE. 30 files, 0 errors.
Items 1-2 of 4.5+ done. Items 3+4 merged into single implementation.

### Commits This Session
| SHA | What |
|-----|------|
| `99505e2` | Fix audit mode graph routing + docs gaps (dev commands, tsconfig, JSDoc gotcha) |
| `266aea0` | BlockOutput type for AI-orchestrated blocks (UC-MW-21) |
| `bca7337` | isolation.rego + wire repo into block executor |
| (pending) | Use case updates + open questions (UC-MW-20,22,23,24,25) |

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

## 4.5+ Remaining: Subagent + Hooks Integration (merged items 3+4)

Items 3 (subagent execution routing) and 4 (hooks generation) merged because agent configs are the central artifact containing tools, hooks, subagent settings, and MCP servers.

### What to implement:
- Enhance promote block's agent config generation (comprehensive configs with hooks, subagent settings, mcpServers)
- Create shared hook scripts (`~/.kiro/hooks/opa-profile.sh`, `~/.kiro/hooks/cortex-gate.sh`)
- Document convention: BlockOutput tells Claude when to spawn subagents

### New/updated use cases (in ARCHITECTURE.md):
- UC-MW-20: Agent configs now include hooks, toolsSettings.subagent, mcpServers, resources, prompt
- UC-MW-22: Mechanism clarified — BlockOutput → Claude → use_subagent
- UC-MW-23: Hooks are per-agent in config; scripts are reusable
- UC-MW-24: Claude as bridge between LangGraph and AI-orchestrated blocks
- UC-MW-25: Meta-workflow proposes hooks (workflow-specific or reusable)

### Open questions (resolve before implementing):
1. Does `run_workflow` MCP tool need step-by-step mode for AI-orchestrated blocks, or separate `run_block` tool?
2. How does BlockOutput.suggested_next_step encode "spawn subagent X with task Y"? Structured convention or free text?

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

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
