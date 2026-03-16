# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5 meta-workflow blocks COMPLETE. 30 files, 0 errors.
Q1 and Q2 both resolved. Implementation remaining: enhance promote block.

### Commits This Session
| SHA | What |
|-----|------|
| `99505e2` | Fix audit mode graph routing + docs gaps |
| `266aea0` | BlockOutput type for AI-orchestrated blocks (UC-MW-21) |
| `bca7337` | isolation.rego + wire repo into block executor |
| `71684a2` | Use case updates (UC-MW-20,22,23,24,25) |
| `549b326` | Segment model + Q1 resolution |
| (pending) | NextStep type + Q2 resolution |

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ Q1 | done | Segment model — single run_workflow tool with interrupt/resume |
| 4.5+ Q2 | done | NextStep discriminated union — structured output for Claude orchestration |

## Design Decisions (Q1 + Q2)

### Q1: Segment Model (resolved)
Single `run_workflow` MCP tool with interrupt/resume. No separate `run_block` tool.

- Workflow = sequence of deterministic LangGraph segments
- Between segments: Claude orchestrates (Sequential Thinking pattern)
- `run_workflow` runs until AI boundary (interrupt), returns BlockOutput
- Claude does its work, calls `run_workflow` with same `thread_id` to resume
- Reusable segments (UC-MW-18) are sub-graphs that compose transparently

### Q2: NextStep Type (resolved)
Structured discriminated union (not free text). Claude maps each variant to a specific action:

```typescript
type NextStep =
  | { type: "resume"; context?: string }        // call run_workflow
  | { type: "spawn_subagent"; agent: string; task: string }  // call use_subagent
  | { type: "ask_user"; question: string; options?: string[] }  // present to user
  | { type: "complete"; summary: string }       // done
```

Design follows Sequential Thinking MCP pattern: structured outputSchema → Claude parses → decides action.

References:
- Sequential Thinking MCP: https://www.npmjs.com/package/@modelcontextprotocol/server-sequential-thinking
- Anthropic advanced tool use: https://www.anthropic.com/engineering/advanced-tool-use

## Implementation Remaining

- Enhance promote block's agent config generation (hooks, subagent settings, mcpServers)
- Create shared hook script conventions
- Document BlockOutput → Claude → use_subagent flow in agent config prompts

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
- Segment model + NextStep design: ARCHITECTURE.md sections "Segment Model" and "NextStep Design"

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
