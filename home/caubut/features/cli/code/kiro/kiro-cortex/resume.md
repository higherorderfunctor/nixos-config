# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 34 files, 0 errors.
**Next: Restart kiro-cli session to retest list_workflows live, then finish validation checklist items 4-7, then Phase 5.**

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports, Config for env, Effect.log* for logging |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ | done | Segment model, NextStep union, UC-MW-26/27/28, hook conventions, artifact templates |
| UC-MW-29 | done | Gap-analyze block: cross-system completeness checks, wired into audit mode |

### Uncommitted Changes

None — all changes committed.

## Meta-Workflow Self-Maintenance

**Fixed in agent config:**
- `@kiro-cortex` in allowedTools (can use own MCP without prompts)
- Prompt moved to `file://./prompts/meta-workflow.md`
- Self-identification in prompt ("Your workflow ID is meta-workflow")
- agentSpawn hook shows git log + status
- Resource paths fixed (absolute `file:///`)
- toolsSettings.fs_write.allowedPaths for write restrictions
- knowledgeBase resource for ARCHITECTURE.md
- fs_write, execute_bash, git tools in allowedTools
- Model pinned to `claude-opus-4.6` (reasoning-heavy workflow design)
- `thinking` tool removed from allowedTools (prefer `sequentialthinking` MCP)

**Filesystem export (UC-MW-16/17): RESOLVED.**
export.ts writes workflow.yaml, author.ts writes instructions/*.yaml, wire.ts writes pipeline.yaml. seed.ts reads YAML back. MCP tool `reload_workflows` triggers re-seed. 34 files, 0 errors.

**UC-MW-29 Gap Analysis: RESOLVED.**
Implemented as block in meta-workflow graph (`src/meta-workflow/gap-analyze.ts`). Design decision: block (not reusable segment, skill, or subagent) because gap-analyzing workflows is meta-workflow's job. Checks filesystem artifacts, pipeline↔instruction consistency, block coverage. Wired: `route(audit) → gap-analyze → optimize → interview`. Deterministic, no interrupt.

**MCP+Backend Blocker: RESOLVED.**
Previously the MCP stdio server (`mcp.ts`) was a proxy to a separate HTTP backend process. Now `mcp.ts` imports `main.ts` directly, starting the HTTP backend (port 3100) in-process. No separate `bun run src/index.ts` needed. Race condition fixed: single `Effect.gen` program forks backend, polls `/health` until ready, then connects MCP transport.

**Validation checklist (before Phase 5):**
1. [x] Start kiro-cli from nixos-config root (not kiro-cortex subdir) for LSP/λ
2. [ ] Switch to meta-workflow agent (Ctrl+Shift+M)
3. [x] Verify `list_workflows` works — stdio test confirmed clean JSON-RPC + correct response (8a7d49c)
4. [~] Verify agent can identify itself in workflow list — MCP connection fails in kiro-cli ("Unable to connect") despite manual `bun run src/mcp.ts` working. Debug file logger added (CORTEX_DEBUG=true → /tmp/kiro-cortex-mcp.log). Next: set CORTEX_DEBUG=true in MCP config env, restart kiro-cli, check log for failure point.
5. [ ] Test update mode on meta-workflow itself — blocked on item 4
6. [x] Verify prompt file loads correctly — confirmed: workflow ID is meta-workflow, all interaction patterns (build/update/refine/audit/self-maintenance) present
7. [~] Verify knowledgeBase resource indexes ARCHITECTURE.md — ARCHITECTURE.md exists and is comprehensive, but cannot confirm kiro-cli indexing until MCP connects (item 4)
8. [x] Verify λ icon appears (code intelligence active)

## Items for Interaction-Analysis (Future)

- F1: "workflow-audit" skill — periodic optimization
- F2: "workflow-metrics" subagent — usage tracking
- F3: "pattern-detector" skill — DRY across workflows
- F4: Meta-workflow self-analysis for interview improvement

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
  meta-workflow/{state,route,interview,research,decompose,optimize,gap-analyze,author,wire,promote,export,seed,graph}.ts
  Sql.ts, main.ts, mcp.ts, index.ts (doc-only), migrations/
policies/access.rego, scoping.rego, isolation.rego
```

## Dependencies (pinned exact)
effect 3.19.19, @effect/platform 0.94.5, @effect/sql 0.49.0, @effect/sql-pg 0.50.3
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
@modelcontextprotocol/sdk 1.27.1, zod 4.3.6, yaml 2.8.2. NO @effect/schema.
