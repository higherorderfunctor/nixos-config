# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. 30 files, 0 errors.
**Next: Meta-workflow self-maintenance validation, then Phase 5.**

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ | done | Segment model, NextStep union, UC-MW-26/27/28, hook conventions, artifact templates |

## Meta-Workflow Self-Maintenance (Gap Analysis Done)

**Fixed in agent config:**
- `@kiro-cortex` in allowedTools (can use own MCP without prompts)
- Prompt moved to `file://./prompts/meta-workflow.md`
- Self-identification in prompt ("Your workflow ID is meta-workflow")
- agentSpawn hook shows git log + status
- Resource paths fixed (absolute `file:///`)
- toolsSettings.fs_write.allowedPaths for write restrictions
- knowledgeBase resource for ARCHITECTURE.md
- fs_write, execute_bash, git tools in allowedTools

**Blocking for full self-maintenance:**
- ~~UC-MW-16/17 (filesystem export)~~ **RESOLVED.** export.ts writes workflow.yaml, author.ts writes instructions/*.yaml, wire.ts writes pipeline.yaml. seed.ts reads YAML back. MCP tool `reload_workflows` triggers re-seed. 32 files, 0 errors.

**Validation checklist (before Phase 5):**
1. Switch to meta-workflow agent (Ctrl+Shift+M)
2. Verify list_workflows works without permission prompt
3. Verify agent can identify itself
4. Test update mode on meta-workflow
5. Verify prompt file loads
6. Verify knowledgeBase indexes ARCHITECTURE.md

## Items for Interaction-Analysis (Future)

- F1: "workflow-audit" skill — periodic optimization
- F2: "workflow-metrics" subagent — usage tracking
- F3: "pattern-detector" skill — DRY across workflows
- F4: Meta-workflow self-analysis for interview improvement

## Gap Analysis as Meta-Workflow Capability

Meta-workflow should be able to gap-analyze itself and any workflow it manages. This is a meta-task: "given a workflow's current state (code, config, docs, use cases), identify what's missing, broken, or inconsistent."

Open design question: should gap analysis be a block in the meta-workflow graph, a reusable segment, a standalone skill, or a subagent task? Discuss with meta-workflow agent to determine the right artifact type. Considerations:
- It needs read access to code, config, docs, and ARCHITECTURE.md (parent context tools)
- It needs to compare use cases against implementation (reasoning-heavy)
- It could be triggered manually ("gap analyze meta-workflow") or as part of audit mode
- It may overlap with the existing optimize block (which checks bloat/spaghetti/DRY)
- Gap analysis is broader than optimize: it checks config, symlinks, MCP registration, agent config completeness, not just instruction quality

Resolve this when switching to meta-workflow agent.

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
