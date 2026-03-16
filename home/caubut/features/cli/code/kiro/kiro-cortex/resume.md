# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5 meta-workflow blocks COMPLETE. 30 files, 0 errors.
Q1 and Q2 both resolved. New use cases UC-MW-26,27,28 added.

### Commits This Session
| SHA | What |
|-----|------|
| `99505e2` | Fix audit mode graph routing + docs gaps |
| `266aea0` | BlockOutput type for AI-orchestrated blocks (UC-MW-21) |
| `bca7337` | isolation.rego + wire repo into block executor |
| `71684a2` | Use case updates (UC-MW-20,22,23,24,25) |
| `549b326` | Segment model + Q1 resolution |
| `a089b36` | NextStep discriminated union + Q2 resolution |
| (pending) | Skills + meta-workflow as agent + context optimization (UC-MW-26,27,28) |

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

## Design Decisions

### Q1: Segment Model (resolved)
Single `run_workflow` MCP tool with interrupt/resume. No separate `run_block` tool.

### Q2: NextStep Type (resolved)
Structured discriminated union: resume, spawn_subagent, ask_user, complete.

### Skills vs Agents (UC-MW-26)
During interview, meta-workflow asks: "How will this workflow be triggered?"
- Dedicated agent: user switches explicitly (focused context)
- Skill: default agent activates on request match (on-demand)
Determines whether promote generates agent config or SKILL.md.
Ref: https://kiro.dev/docs/cli/skills/

### Meta-Workflow as Top-Level Agent (UC-MW-27)
Meta-workflow itself is a dedicated agent (`~/.kiro/agents/meta-workflow.json`), not always in context. User switches to it when designing/updating workflows. Critical for 1M instructions goal.

### Context Optimization (UC-MW-28)
Meta-workflow proposes the right artifact type based on context budget:
- Skills: on-demand by description matching (lowest context cost)
- Agents: dedicated focused work (loaded only when switched to)
- Subagents: fresh context, parallel execution
- MCPs: external tools, not in context until called

## Implementation Remaining

- Enhance promote block: generate skill (SKILL.md + references/) OR agent config based on UC-MW-26
- Enhance interview block: add trigger selection question (dedicated agent vs skill)
- Create meta-workflow agent config (`~/.kiro/agents/meta-workflow.json`)
- Enhance promote block: comprehensive agent configs (hooks, subagent settings, mcpServers)
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
- Skills docs: https://kiro.dev/docs/cli/skills/
- Agent Skills standard: https://agentskills.io
- Segment model + NextStep design: ARCHITECTURE.md sections "Segment Model" and "NextStep Design"

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
