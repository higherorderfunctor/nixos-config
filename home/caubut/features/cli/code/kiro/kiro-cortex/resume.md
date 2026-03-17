# kiro-cortex Resume — 2026-03-17

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 33 files, 0 errors, 0 warnings.
Validation checklist: **9/9 complete** — all 5 smoke tests pass.
**Next: Review ARCHITECTURE.md flow diagram against use cases, then Phase 5.**

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports, Config for env, Effect.log* for logging |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ | done | Segment model, NextStep union, UC-MW-26/27/28, hook conventions, artifact templates |
| UC-MW-29 | done | Lint-artifacts block: cross-system structural completeness checks, wired into audit mode |
| Cleanup | done | MCP rewrite to @effect/ai (stdio, no HTTP), tagged WorkflowError, unused deps removed, YAML export complete |

## Meta-Workflow Self-Maintenance

**Agent config:** `@kiro-cortex` in allowedTools, prompt at `file://./prompts/meta-workflow.md`, self-identification, agentSpawn hook (git log + status), absolute resource paths, fs_write allowedPaths, knowledgeBase for ARCHITECTURE.md, model pinned to `claude-opus-4.6`.

**MCP Architecture:** Pure Effect via `@effect/ai` McpServer.layerStdio (stdin Stream, stdout Sink). No HTTP server, no port, no race condition on agent switch. Tools: `list_workflows`, `run_workflow`, `reload_workflows`.

**Filesystem export (UC-MW-16/17):** Complete. export.ts writes workflow.yaml, author.ts writes instructions/*.yaml, wire.ts writes pipeline.yaml. seed.ts reads YAML back. All 10 blocks have instruction YAMLs. `reload_workflows` MCP tool triggers re-seed.

**Validation checklist (before Phase 5):**
1. [x] Start kiro-cli from nixos-config root for LSP/λ
2. [x] Switch to meta-workflow agent — MCP tools responding
3. [x] Verify `list_workflows` works — confirmed (8a7d49c)
4. [x] Verify agent can identify itself in workflow list
5. [x] Test update mode — route + interview interrupt works, bugs fixed (ce3c3ad)
6. [x] Verify prompt file loads correctly
7. [x] Verify knowledgeBase resource indexes ARCHITECTURE.md
8. [x] Verify λ icon appears (code intelligence active)
9. [x] Smoke test all 5 mode paths — **5/5 pass** (57fdb69, 91cf496)

### Smoke Test Results (2026-03-17)

**Finding:** Agent must pass `mode` (and `workflow_id` for targeted ops) explicitly to `run_workflow`. The route block is deterministic — dispatches on `state.mode`, not natural language.

| Mode | Input | Route | Status |
|------|-------|-------|--------|
| Build | `{mode: "build"}` | → interview ✅ | ✅ pass |
| Update | `{mode: "update", workflow_id: "..."}` | → interview (update prompt) ✅ | ✅ pass |
| Self-Maint | (= update + meta-workflow) | → interview ✅ | ✅ pass |
| Refine | `{mode: "refine", workflow_id: "..."}` | → author ✅ | ✅ pass |
| Audit | `{mode: "audit"}` | → lint-artifacts → optimize ✅ | ✅ pass |

**Bugs fixed:**
- **author.ts** (57fdb69): Crashed on `state.blocks` undefined in refine mode. Fix: early return guard.
- **gap-analyze.ts** (57fdb69): Renamed to `lint-artifacts.ts`. Originally crashed on `path.join` with undefined `workflow_name` in audit-all mode. Fix: scan `workflows/` dir when no name; guard `state.blocks?.length`.
- **optimize.ts** (91cf496): Crashed on `state.blocks.length` in audit mode (no blocks in state). Fix: early return guard `if (!state.blocks?.length)`.

**Note:** `bun build` to `dist/` is unnecessary — MCP config runs `bun run src/mcp.ts` directly.

### Flow Diagram Review (WIP — 2026-03-17)

**Problem:** Hand-drawn ASCII flow diagram in ARCHITECTURE.md had hallucinated lines, inconsistent arrows, and misaligned mode paths vs documented use cases.

**Approach:** Built `scripts/render-diagram.ts` — a grid-based deterministic ASCII renderer (Bun + TS, zero deps). Nodes placed on explicit grid positions, edges drawn with Manhattan routing. No auto-layout. Source of truth for the diagram.

**Tooling evaluated:** `mermaid-ascii` (Go, 1.3k stars, active) — good for simple graphs but auto-layout fails on complex multi-branch convergence. `graph-easy` (Perl) — abandoned 16 years. Decision: custom renderer for manual layout control.

**Misalignments found (diagram vs ARCHITECTURE.md Mode Paths):**
1. REFINE: diagram showed route → author → END. Correct: route → interview → author → END
2. AUDIT: diagram dead-ended at decompose. Correct: full path through author → wire → promote → END
3. PROGRAMMATIC: diagram only showed FAIL case. Correct: decompose → optimize → author → wire → promote → END (FAIL only on invalid input)

**Current state:** Renderer produces correct 3-column layout (build|audit|programmatic) with convergence into shared tail. WIP — need to review full flow end-to-end against use cases before replacing ARCHITECTURE.md diagram.

**Resume prompt:** "Read resume.md. We were reviewing the ARCHITECTURE.md flow diagram. The renderer at scripts/render-diagram.ts produces a corrected diagram. Run it to see current output. We need to: (1) walk through each mode path end-to-end to verify it matches the use cases in ARCHITECTURE.md, (2) check if the refine short-circuit (interview → author, skipping research/decompose/optimize) is clear in the diagram, (3) once verified, replace the Flow Diagram section in ARCHITECTURE.md with the rendered output, (4) commit and move to Phase 5."

## Pre-Phase 5 TODO

- ~~Rename `gap-analyze` block~~ — DONE: renamed to `lint-artifacts`. Name now reflects it's a structural consistency checker (filesystem lint), not semantic analysis.
- Subagent context reset strategy. Subagent tool restrictions are mostly workable: `thinking` → Sequential Thinking MCP, `grep`/`glob` → bash, `fetch` → MCP fetch server, `introspect`/`todo_list` → not needed. Only `web_search` requires root agent. Autonomous blocks (lint-artifacts, optimize, decompose, author, wire, export) should run as subagents for context shedding — only the summary returns to parent, not the full RAG payload. HITL blocks (interview, research, promote) stay in root agent. Add use case(s) to ARCHITECTURE.md, update block table with execution_env recommendations, configure subagent MCP access (kiro-cortex, OpenMemory, Sequential Thinking, fetch).
  - **Design proposal drafted (2026-03-17):** Use existing interrupt() pattern — block executor checks execution_env, if "subagent" it interrupts with spawn payload instead of running block.execute(). Claude spawns subagent, gets summary, resumes. No graph changes needed.
  - **Block classification:** root agent = route (inline), interview, research, decompose, optimize, promote (all HITL). Subagent = lint-artifacts, author, wire, export (all autonomous).
  - **Subagent MCPs:** kiro-cortex (RAG), OpenMemory, Sequential Thinking, fetch. Built-in: read, write, shell, code.
  - **Open questions:** (1) per-block vs per-segment subagents, (2) should programmatic mode be fully autonomous (single subagent for entire flow), (3) generic vs specialized subagent agent configs, (4) author block RAG access — via kiro-cortex MCP or task description, (5) update workflow.yaml execution_env now or at implementation time.
- Multi-instruction YAML format + hierarchical disk layout (UC-MW-30, UC-MW-31). Current model is 1 instruction per YAML, 1 YAML per block — won't scale to millions. Need:
  - Array of instructions per YAML file (each gets its own vector in pgvector)
  - Directory hierarchy for organization: `instructions/<domain>/<topic>.yaml` (e.g., `effect/effect-stream.yaml`, `effect/effect-http-api.yaml`)
  - Seed.ts updated to walk directories recursively and parse multi-instruction files
  - Author block needs guidance on chunking: one concept per instruction for optimal retrieval
- Semantic gap analysis + per-workflow arch docs (UC-MW-32, UC-MW-33). Current lint-artifacts is filesystem lint. The meta-workflow needs a separate capability that:
  - Maintains an ARCHITECTURE.md per workflow (generated from interview + refinements over time)
  - Captures use cases during interview, stores them as testable assertions
  - Compares designed flow (blocks, pipeline, instructions) against documented use cases + arch
  - Uses LLM to reason about coverage gaps: "UC-3 says X but no block handles X"
  - Mirrors how we work now: arch doc is source of truth, diagram/flow must align with it
  - Could be a new block (e.g., `validate`) or an LLM-powered mode of the existing audit path
  - Interview refinements accumulate in the arch doc — not lost between sessions
- Load/validation test. Seed pgvector with ~100K instructions across multiple domains/repos. Run a complex multi-block workflow with mocked HITL (auto-answer interrupts). Validate: (1) OPA scoping returns correct filtered set at scale, (2) RAG retrieval stays relevant — no context drift/dilution from unrelated instructions bleeding in, (3) block executor injects only scoped instructions, (4) subagent context shedding works — parent context doesn't grow with RAG payload. Goal: prove the OPA→RAG pipeline holds at scale before building real workflows on top of it.

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
  meta-workflow/{state,route,interview,research,decompose,optimize,lint-artifacts,author,wire,promote,export,seed,graph}.ts
  Sql.ts, mcp.ts, index.ts (doc-only)
  migrations/{0001_init,0002_add_instruction_columns,0003_add_content_hash,_schema.sql}.ts
scripts/
  render-diagram.ts  # deterministic ASCII flow diagram renderer
workflows/
  meta-workflow/
    workflow.yaml, pipeline.yaml
    instructions/{route,interview,research,decompose,optimize,author,wire,promote,export,lint-artifacts}.yaml
policies/
  access.rego, scoping.rego, isolation.rego
```

## Dependencies (pinned exact)
effect 3.20.0, @effect/ai 0.34.0, @effect/platform 0.95.0, @effect/platform-bun 0.88.0
@effect/platform-node 0.105.0, @effect/sql 0.50.0, @effect/sql-pg 0.51.0
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
pg 8.20.0, yaml 2.8.2. NO @effect/schema. NO zod.
