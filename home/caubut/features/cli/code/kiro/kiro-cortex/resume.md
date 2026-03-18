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

## Phase 5: Task-Scoped Interview + Implementation

### Approach

Interviews scoped per-task. Each task has its own interview (if needed), then implementation. Later answers depend on seeing earlier results — no upfront 14-question marathon.

### Dependency Order

```
5.1: Interview (flow Q1-6) → Implement flow redesign
  ↓
5.2: Interview (validate Q7-10) → Implement validate block
  ↓
5.3: Interview (subagent Q11-14) → Implement subagent support
  ↓
5.4: Multi-instruction YAML (no interview) — can run parallel with 5.1-5.3
  ↓
5.5: Context budget / RAG adequacy (mini-interview if needed)
  ↓
5.6: Load test at 100K
  ↓
5.7: Documentation finalization
  ↓
Phase 6: Repo-Analysis
```

### 5.1: Flow Redesign (INTERVIEW → IMPLEMENT)

**Status: INTERVIEW IN PROGRESS**

#### Interview Questions (6)

1. Confirm: unified flow with 2 entry points (interactive / programmatic). No separate modes. Interview adapts. Validate runs on every flow. Yes/no?
2. Validate → interview loop: full re-pass (interview → decompose → ... → validate) or short-circuit to just affected blocks?
3. Cross-workflow "refactor everything" (UC-MW-13): run the flow once per workflow? Or a separate capability?
4. Mode field in state: replace with context detection (workflow_id/block_id/structured_input presence)? Or keep mode with 2 values (interactive/programmatic)?
5. Export block: keep separate or fold into author/wire/promote (each exports its own artifacts)?
6. Naming: "validate" for the new block? Or "check"/"verify"/something else?

#### Decisions

_(filled in as interview progresses)_

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

#### New Use Cases (proposed)

- **UC-MW-34**: Interview adapts behavior based on state context (build/update/refine/validate-callback are one block with adaptive instructions)
- **UC-MW-35**: Validate block — autonomous loop before promote. Structural checks (UC-MW-29) + scoped re-optimize (UC-MW-14) + cross-workflow DRY (UC-MW-13) + semantic gap analysis (UC-MW-33). Loops until clean, raises discrepancies to interview.
- **UC-MW-36**: Validate → interview → decompose loop (discrepancy resolution path). When validate finds issues needing human judgment, it interrupts back to interview. After resolution, flow continues through decompose → ... → validate again.

#### Implementation (after interview)

- Redesign graph.ts with simplified edges
- Update route.ts (remove mode switch, context-based routing)
- Update interview.ts (adaptive behavior based on state)
- Update state.ts (remove/simplify mode field, add block_id)
- Update render-diagram.ts for new flow
- Smoke test all paths

### 5.2: Validate Block (INTERVIEW → IMPLEMENT)

**Status: BLOCKED on 5.1**

Depends on 5.1 — need to see the implemented flow before designing validate's behavior.

#### Interview Questions (4)

7. UC-MW-32 (per-workflow arch docs): created during interview? Validate checks against it?
8. UC-MW-33 (semantic gap analysis): is this the validate block, or a sub-step within it?
9. Should validate attempt autonomous fixes or only report? (User said "loop until analysis is complete with option to raise discrepancies")
10. What checks does validate run? Proposed list:
    - Structural completeness (filesystem artifacts, pipeline↔block consistency) — from UC-MW-29
    - Instruction bloat per block (UC-MW-8) — currently in optimize
    - Cross-workflow DRY (UC-MW-10/13) — currently in optimize
    - Scoped re-optimize: can this workflow reuse global patterns? Context budget? (UC-MW-14)
    - Semantic gap: use cases vs implementation coverage (UC-MW-33)

#### Decisions

_(filled in as interview progresses)_

#### Implementation (after interview)

- New validate block (refactored from lint-artifacts)
- Update optimize.ts (move cross-workflow checks to validate, keep local checks)
- Wire validate into graph between wire and promote
- Smoke test validate loop

### 5.3: Subagent Design (INTERVIEW → IMPLEMENT)

**Status: BLOCKED on 5.2**

Depends on 5.2 — need to see validate block behavior before deciding subagent boundaries.

#### Interview Questions (4)

11. Validate as subagent: autonomous loop that can interrupt back to root? Or stays in root agent?
12. Per-block vs per-segment: spawn one subagent per autonomous block, or one per autonomous segment (multiple blocks)?
13. Programmatic mode: single subagent for entire flow (no HITL needed)?
14. Author RAG: subagent calls kiro-cortex MCP directly, or root agent pre-fetches and passes via task description?

#### Background

**Design proposal (from 2026-03-17):** Use existing interrupt() pattern — block executor checks execution_env, if "subagent" it interrupts with spawn payload. Claude spawns subagent, gets summary, resumes. No graph changes needed.

**Block classification (needs review post-redesign):**
- Root agent (HITL): route (inline), interview, research, promote
- Subagent candidates (autonomous): validate, author, wire, export, decompose, optimize
- Key question: validate is autonomous but needs to raise to interview — how does this work across subagent boundary?

**Subagent MCPs:** kiro-cortex (RAG), OpenMemory, Sequential Thinking, fetch. Built-in: read, write, shell, code.

#### Decisions

_(filled in as interview progresses)_

#### Implementation (after interview)

- Update workflow.yaml execution_env per block
- Generate subagent agent configs
- Wire subagent spawn into block executor
- Smoke test subagent paths

### 5.4: Multi-instruction YAML + Hierarchical Layout (UC-MW-30/31)

**Status: READY (no interview needed, independent of 5.1-5.3)**

Can run in parallel with flow redesign tasks.

- Array of instructions per YAML (each gets own vector in pgvector)
- Directory hierarchy: `instructions/<domain>/<topic>.yaml`
- Seed.ts: recursive directory walk + multi-instruction parsing
- Author block: chunking guidance (one concept per instruction)
- Backward compat with single-instruction files

### 5.5: Context Budget Analysis + RAG Adequacy

**Status: BLOCKED on 5.2 + 5.4**

Needs validate block (5.2) + enough instructions to test with (5.4). May need mini-interview after seeing results.

The OPA→RAG pipeline has an unresolved gap: blocks get a hard `max_results` limit (20 or 50) from OPA scoping, and the executor does a single pgvector search using only the block's description as the embedding query. If a block genuinely needs more instructions than the limit, they're silently dropped. No warning, no fallback, no multi-query.

**Current behavior (gap):**
- `scoping.rego` returns `max_results: 20` (or 50 for analysis tasks) — hard LIMIT on pgvector
- `Executor.ts` embeds `block.description` once, searches once, takes top N
- No cosine distance threshold — returns `max_results` even if tail results are barely relevant
- No multi-query (e.g., description + state-derived sub-queries + deduplication)
- `optimize.ts` checks block count and DRY but NOT whether instructions are being truncated
- No mechanism for a block to declare "I need more context than the default"

**What this step must resolve:**
1. How does the system detect when a block's relevant instruction set exceeds `max_results`?
2. Should blocks declare a context budget? (e.g., `max_context` in BlockDef or OPA per-block overrides)
3. Should the executor support multi-query RAG?
4. Should there be a cosine distance cutoff?
5. How does validate/optimize use this?
6. At 100K+ instructions, how do we ensure the right 20 surface?

### 5.6: Load/Validation Test at 100K Instructions

**Status: BLOCKED on 5.1-5.5**

- Seed pgvector with ~100K instructions across multiple domains
- Run complex multi-block workflow with mocked HITL
- Validate: OPA scoping at scale, RAG relevance (no context drift), block executor injection, subagent context shedding, context budget adequacy (no silent truncation)
- Goal: prove OPA→RAG pipeline holds at scale before building real workflows

### 5.7: Documentation Finalization

**Status: BLOCKED on 5.1-5.6**

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

Read resume.md. Phase 5 in progress. Interviews scoped per-task — each task has its own interview, then implementation.

Key context:
1. Phase 5 restructured into 7 tasks (5.1-5.7), each with scoped interview before implementation.
2. 5.1 (flow redesign) interview IN PROGRESS — 6 questions about flow structure.
3. 5.2 (validate block) BLOCKED on 5.1 — 4 questions, need to see flow before designing validate.
4. 5.3 (subagent design) BLOCKED on 5.2 — 4 questions, need to see validate before deciding subagent boundaries.
5. 5.4 (multi-instruction YAML) READY — no interview needed, can run parallel with 5.1-5.3.
6. Three bugs found in current graph — all subsumed by redesign.
7. `gap-analyze` already renamed to `lint-artifacts` across all code/docs.

Next step: Interview user on 5.1 questions (Q1-6: flow structure) one at a time, recording decisions as we go.
