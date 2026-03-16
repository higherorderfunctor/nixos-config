# kiro-cortex Resume — 2026-03-16

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 34 files, 0 errors.
**Next: Fix HITL resume bug (bug 2 below), then Phase 5.**

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

MCP rewrite to @effect/ai, dependency updates, removed @modelcontextprotocol/sdk + zod.

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

**MCP Architecture: REWRITTEN — @effect/ai replaces @modelcontextprotocol/sdk.**
Previously `mcp.ts` was a callback-based MCP server using `@modelcontextprotocol/sdk` that proxied to an HTTP backend on port 3100. This caused a port race condition when kiro-cli switched agents (old instance shutting down, new instance starting up, both fighting for port 3100).

Root cause analysis: the HTTP server was never consumed by anything except the MCP tool handlers themselves — LangGraph and OPA are in-process libraries, not HTTP clients. The HTTP layer was vestigial from an earlier architecture where mcp.ts was a separate process.

Fix: replaced the entire HTTP+callback stack with `@effect/ai`'s `McpServer.layerStdio`. This is a fully Effect-native MCP server that reads stdin as a Stream and writes stdout as a Sink. Tool handlers are Effects with direct service access via layers — no HTTP, no port, no callback bridging, no `runPromise`.

What was eliminated:
- HTTP server on port 3100 (and the agent-switch race condition)
- `@modelcontextprotocol/sdk` dependency
- `zod` dependency (was only used for MCP tool schemas)
- `ensureBackend`, `waitForBackend`, health polling
- All `fetch("localhost:3100/...")` calls
- `connectMcp` as `Effect.async<never>` hack
- Forked-fiber startup dance

What replaced it:
- `@effect/ai` McpServer with `layerStdio` (stdin Stream, stdout Sink)
- Tools defined with `Tool.make` + `Toolkit.make` (Effect Schema)
- Handlers via `CortexToolkit.toLayer` — Effects with direct service access
- `loadInstructions` runs during layer construction (before tools accept calls)
- Single `Layer.launch(ServerLayer)` — clean Effect-native lifecycle

**Validation checklist (before Phase 5):**
1. [x] Start kiro-cli from nixos-config root (not kiro-cortex subdir) for LSP/λ
2. [x] Switch to meta-workflow agent — confirmed, MCP tools responding
3. [x] Verify `list_workflows` works — stdio test confirmed clean JSON-RPC + correct response (8a7d49c)
4. [x] Verify agent can identify itself in workflow list — confirmed: sees meta-workflow with correct description
5. [⚠] Test update mode on meta-workflow — route + interview interrupt works, but **two bugs found** (see below)
6. [x] Verify prompt file loads correctly — confirmed: workflow ID is meta-workflow, all interaction patterns present
7. [x] Verify knowledgeBase resource indexes ARCHITECTURE.md — file exists, well-structured, MCP connects. Can't verify kiro-cli indexing programmatically but all prerequisites met
8. [x] Verify λ icon appears (code intelligence active)

**Bugs found during validation (item 5):**
1. **workflow_id not propagated to state** — FIXED. Added `workflow_id` to state annotation, route node maps it to `workflow_name` via Command update.
2. **HITL resume doesn't advance** — FIXED. `mcp.ts` resume branch checked `params.input === undefined` but callers pass the answer as `input`. Changed to: `thread_id` present → always `Command({ resume: params.input })`. Needs `hm switch` + restart to verify live.

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
  Sql.ts, mcp.ts, index.ts (doc-only), migrations/
policies/access.rego, scoping.rego, isolation.rego
```

## Dependencies (pinned exact)
effect 3.20.0, @effect/ai 0.34.0, @effect/platform 0.95.0, @effect/platform-bun 0.88.0
@effect/sql 0.50.0, @effect/sql-pg 0.51.0
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
yaml 2.8.2. NO @effect/schema. NO zod.
