# kiro-cortex Resume — 2026-03-18

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 33 files, 0 errors, 0 warnings.
Validation checklist: **9/9 complete** — all 5 smoke tests pass.

**Next: Phase 5 (flow redesign + subagent design + remaining UCs), then Phase 6 (repo-analysis).**

### What's Built (all phases)

| Phase | Status | What |
|-------|--------|------|
| 0-3 | done | Core RAG loop: OPA, Embedding, InstructionRepo, LangGraph context assembly |
| 4.1-4.4 | done | Block model, Registry, PipelineExecutor, MCP wrapper, MVP meta-workflow |
| Pre-4.5 | done | OPA per-block injection: access.rego, scoping.rego, YAML loader, block executor |
| Conventions | done | Domain folders, Context.Tag, Schema.transform, .addError, layer exports, Config for env, Effect.log* for logging |
| 4.5 | done | decompose, research, optimize, promote + audit/programmatic modes |
| 4.5+ | done | Segment model, NextStep union, UC-MW-26/27/28, hook conventions, artifact templates |
| UC-MW-29 | done | Lint-artifacts block: cross-system structural completeness checks |
| Cleanup | done | MCP rewrite to @effect/ai (stdio, no HTTP), tagged WorkflowError, unused deps removed, YAML export complete |

## Phase 5: Flow Redesign + Subagent + Remaining UCs

### Overview

Two work streams merged into one dependency-ordered plan:

**Stream A — Flow Redesign:** Collapse 6 modes (build/update/refine/audit/programmatic/scoped-reoptimize) into a unified flow with 2 entry points. Add a "validate" block that runs before promote on every flow. Interview adapts based on context rather than mode.

**Stream B — Remaining work:** Subagent design, multi-instruction YAML (UC-MW-30/31), per-workflow arch docs (UC-MW-32), semantic gap analysis (UC-MW-33), load test at 100K.

### Dependency Order

```
5.1: Flow Redesign + Subagent Design + Validate Block Design
  ↓  (tightly coupled — designed together, requires interview)
5.2: Implementation — graph.ts, new/modified blocks, state changes
  ↓
5.3: Multi-instruction YAML + Hierarchical Layout (UC-MW-30/31)
  ↓  (independent of flow, but needed before repo-analysis generates many instructions)
5.4: Load/Validation Test at 100K Instructions
  ↓
5.5: Documentation Finalization — ARCHITECTURE.md, diagram, sequence diagram, README
  ↓
Phase 6: Repo-Analysis
```

### 5.1: Flow Redesign + Subagent + Validate (NEEDS INTERVIEW)

#### Proposed Unified Flow

```
route → [interview ↔ research] → decompose → optimize → author → wire → validate ↔ [interview] → promote → export → END
                                    ↑                                         │
                                    └── programmatic enters here              │
                                                                  raises discrepancies
                                                                  back to interview
```

**Route simplification:**
- `workflow_id` provided → load existing workflow into state (was UPDATE)
- `structured_input` provided → skip to decompose (was PROGRAMMATIC)
- Neither → fresh start (was BUILD)
- No mode switch needed. Route sets up context.

**Interview adapts based on state context:**
- No existing workflow → "What do you want to build?" (was BUILD)
- Existing workflow loaded → "What do you want to change?" (was UPDATE)
- Existing workflow + `block_id` → narrows to that block (was REFINE)
- Called back from validate → "Here are discrepancies, how should we resolve?"

**Validate block (new, replaces standalone audit/lint-artifacts modes):**
- Runs before promote on EVERY flow
- Subsumes: UC-MW-29 (structural completeness), UC-MW-14 (scoped re-optimize), UC-MW-13 (cross-workflow DRY)
- Autonomous loop: checks → fixes what it can → raises discrepancies to interview if human input needed
- On clean → promote

**What this eliminates:**
- REFINE mode → interview with `block_id` in state
- AUDIT mode → validate step on every flow
- SCOPED RE-OPTIMIZE mode → validate step on every flow
- BUILD vs UPDATE distinction → interview adapts based on whether workflow exists
- Separate lint-artifacts entry point → lint-artifacts logic moves into validate

#### Use Case Impact

| UC | Current | Proposed |
|----|---------|----------|
| UC-MW-1 (build) | BUILD mode | Interactive, no workflow_id |
| UC-MW-2 (update) | UPDATE mode | Interactive, workflow_id provided |
| UC-MW-3 (refine) | REFINE mode | Interactive, workflow_id + block_id |
| UC-MW-4/12 (programmatic) | PROGRAMMATIC mode | structured_input → skip to decompose |
| UC-MW-13 (cross-wf DRY) | AUDIT mode | Part of validate block |
| UC-MW-14 (scoped re-opt) | SCOPED RE-OPTIMIZE | Part of validate block |
| UC-MW-29 (structural lint) | lint-artifacts block in audit mode | Part of validate block |
| UC-MW-32 (per-wf arch docs) | Not implemented | Interview captures → validate checks against |
| UC-MW-33 (semantic gap) | Not implemented | Part of validate block (LLM-powered) |

#### New Use Cases Needed

- **UC-MW-34**: Interview adapts behavior based on state context (build/update/refine/validate-callback are one block with adaptive instructions)
- **UC-MW-35**: Validate block — autonomous loop before promote. Structural checks (UC-MW-29) + scoped re-optimize (UC-MW-14) + cross-workflow DRY (UC-MW-13) + semantic gap analysis (UC-MW-33). Loops until clean, raises discrepancies to interview.
- **UC-MW-36**: Validate → interview → decompose loop (discrepancy resolution path). When validate finds issues needing human judgment, it interrupts back to interview. After resolution, flow continues through decompose → ... → validate again.

#### Subagent Design (integrated with flow redesign)

**Design proposal (from 2026-03-17):** Use existing interrupt() pattern — block executor checks execution_env, if "subagent" it interrupts with spawn payload. Claude spawns subagent, gets summary, resumes. No graph changes needed.

**Block classification (needs review post-redesign):**
- Root agent (HITL): route (inline), interview, research, promote
- Subagent candidates (autonomous): validate, author, wire, export, decompose, optimize
- Key question: validate is autonomous but needs to raise to interview — how does this work across subagent boundary?

**Subagent MCPs:** kiro-cortex (RAG), OpenMemory, Sequential Thinking, fetch. Built-in: read, write, shell, code.

**Open questions (5 from original + new ones from flow redesign):**
1. Per-block vs per-segment subagents
2. Should programmatic mode be fully autonomous (single subagent for entire flow)?
3. Generic vs specialized subagent agent configs
4. Author block RAG access — via kiro-cortex MCP or task description?
5. Update workflow.yaml execution_env now or at implementation time?
6. Validate as subagent — how does "raise to interview" work across subagent boundary?
7. Does validate run as one long subagent that can interrupt, or does it interrupt back to root which then goes to interview?

#### Interview Questions (for next session)

These must be resolved before implementation:

**Flow structure:**
1. Confirm: unified flow with 2 entry points (interactive / programmatic). No separate modes. Interview adapts. Validate runs on every flow. Yes/no?
2. Validate → interview loop: full re-pass (interview → decompose → ... → validate) or short-circuit to just affected blocks?
3. Cross-workflow "refactor everything" (UC-MW-13): run the flow once per workflow? Or a separate capability?
4. Mode field in state: replace with context detection (workflow_id/block_id/structured_input presence)? Or keep mode with 2 values (interactive/programmatic)?
5. Export block: keep separate or fold into author/wire/promote (each exports its own artifacts)?
6. Naming: "validate" for the new block? Or "check"/"verify"/something else?

**Validate block design:**
7. UC-MW-32 (per-workflow arch docs): created during interview? Validate checks against it?
8. UC-MW-33 (semantic gap analysis): is this the validate block, or a sub-step within it?
9. Should validate attempt autonomous fixes or only report? (User said "loop until analysis is complete with option to raise discrepancies")
10. What checks does validate run? Proposed list:
    - Structural completeness (filesystem artifacts, pipeline↔block consistency) — from UC-MW-29
    - Instruction bloat per block (UC-MW-8) — currently in optimize
    - Cross-workflow DRY (UC-MW-10/13) — currently in optimize
    - Scoped re-optimize: can this workflow reuse global patterns? Context budget? (UC-MW-14)
    - Semantic gap: use cases vs implementation coverage (UC-MW-33)

**Subagent design:**
11. Validate as subagent: autonomous loop that can interrupt back to root? Or stays in root agent?
12. Per-block vs per-segment: spawn one subagent per autonomous block, or one per autonomous segment (multiple blocks)?
13. Programmatic mode: single subagent for entire flow (no HITL needed)?
14. Author RAG: subagent calls kiro-cortex MCP directly, or root agent pre-fetches and passes via task description?

### 5.2: Implementation (after interview resolves questions)

- Redesign graph.ts with simplified edges
- New validate block (or refactored lint-artifacts)
- Update route.ts (remove mode switch, context-based routing)
- Update interview.ts (adaptive behavior based on state)
- Update state.ts (remove/simplify mode field, add block_id, validate state)
- Update optimize.ts (move cross-workflow checks to validate, keep local checks)
- Update render-diagram.ts for new flow
- Smoke test all paths

### 5.3: Multi-instruction YAML + Hierarchical Layout (UC-MW-30/31)

Independent of flow redesign. Needed before Phase 6 generates many instructions.

- Array of instructions per YAML (each gets own vector in pgvector)
- Directory hierarchy: `instructions/<domain>/<topic>.yaml`
- Seed.ts: recursive directory walk + multi-instruction parsing
- Author block: chunking guidance (one concept per instruction)
- Backward compat with single-instruction files

### 5.4: Load/Validation Test at 100K Instructions

Depends on 5.2 and 5.3.

- Seed pgvector with ~100K instructions across multiple domains
- Run complex multi-block workflow with mocked HITL
- Validate: OPA scoping at scale, RAG relevance (no context drift), block executor injection, subagent context shedding
- Goal: prove OPA→RAG pipeline holds at scale before building real workflows

### 5.5: Documentation Finalization

After all implementation.

- ARCHITECTURE.md: updated use cases, flow, block table, diagram, mode paths
- Sequence diagram: updated for unified flow + validate loop
- README: updated status
- Resume: final state for Phase 6 handoff

## Bugs Found (2026-03-18 flow review)

These are subsumed by the flow redesign but documented for reference:

1. **AUDIT path infinite loop in graph.ts**: After decompose → optimize in audit mode, optimize routes back to interview indefinitely. No mechanism to distinguish first-pass scan from second-pass fix. One-line fix: `s.mode === "audit" && !s.needs_redesign && !s.blocks?.length ? "interview"`. Moot after redesign removes audit mode.

2. **REFINE path mismatch**: ARCHITECTURE.md says route → interview → author → END. Actual code (route.ts): route → author → END. No conditional edge from interview → author exists. Moot after redesign collapses refine into adaptive interview.

3. **Missing export block in documented mode paths**: All ARCHITECTURE.md paths end with promote → END but graph.ts has promote → export → END. Moot after redesign updates all paths.

## Meta-Workflow Self-Maintenance

**Agent config:** `@kiro-cortex` in allowedTools, prompt at `file://./prompts/meta-workflow.md`, self-identification, agentSpawn hook (git log + status), absolute resource paths, fs_write allowedPaths, knowledgeBase for ARCHITECTURE.md, model pinned to `claude-opus-4.6`.

**MCP Architecture:** Pure Effect via `@effect/ai` McpServer.layerStdio (stdin Stream, stdout Sink). No HTTP server, no port, no race condition on agent switch. Tools: `list_workflows`, `run_workflow`, `reload_workflows`.

**Filesystem export (UC-MW-16/17):** Complete. export.ts writes workflow.yaml, author.ts writes instructions/*.yaml, wire.ts writes pipeline.yaml. seed.ts reads YAML back. All 10 blocks have instruction YAMLs. `reload_workflows` MCP tool triggers re-seed.

## Items for Interaction-Analysis (Future)

- F1: "workflow-audit" skill — periodic optimization
- F2: "workflow-metrics" subagent — usage tracking
- F3: "pattern-detector" skill — DRY across workflows
- F4: Meta-workflow self-analysis for interview improvement

## Phase 6 — Repo-Analysis (after Phase 5 complete)

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
docs/
  ARCHITECTURE.md, sequence-diagram.txt
```

## Dependencies (pinned exact)
effect 3.20.0, @effect/ai 0.34.0, @effect/platform 0.95.0, @effect/platform-bun 0.88.0
@effect/platform-node 0.105.0, @effect/sql 0.50.0, @effect/sql-pg 0.51.0
@langchain/langgraph 1.2.2, @langchain/langgraph-checkpoint-postgres 1.0.1
pg 8.20.0, yaml 2.8.2. NO @effect/schema. NO zod.

## Resume Prompt

Read resume.md. Phase 5 in progress. Status: NEEDS INTERVIEW before implementation.

Key context:
1. Flow redesign proposed — collapse 6 modes into unified flow + validate block. See "5.1" section for full proposal and interview questions (14 questions).
2. Subagent design integrated with flow redesign — 7 open questions.
3. UC-MW-30..33 not yet implemented. UC-MW-32/33 may fold into the new validate block.
4. Load test at 100K instructions planned for 5.4.
5. Three bugs found in current graph (audit loop, refine mismatch, missing export) — all subsumed by redesign.
6. `gap-analyze` already renamed to `lint-artifacts` across all code/docs.
7. Diagram renderer at `scripts/render-diagram.ts` — needs update after flow redesign.
8. Generic sequence diagram at `docs/sequence-diagram.txt` — needs update after flow redesign.

Next step: Interview user on the 14 questions in 5.1 to resolve open design decisions before implementation.
