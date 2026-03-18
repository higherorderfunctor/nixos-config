# kiro-cortex Resume — 2026-03-18

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 34 files, 0 errors, 0 warnings.
Validation checklist: **9/9 complete** — all 5 smoke tests pass.

**5.1 (flow redesign) COMPLETE. 5.2 (subagent) COMPLETE. 5.3 (package restructure) IN PROGRESS. 5.4 (validate) interview COMPLETE. Next: 5.3 implementation.**

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
5.2: Interview (subagent Q11-14) → Implement subagent support
  ↓
5.3: Package restructure (agents/ split from kiro-cortex core)
  ↓
5.4: Interview (validate Q7-10+Q11) → Implement validate block
  ↓
5.5: Multi-instruction YAML (no interview) — can run parallel with 5.4
  ↓
5.6: Context budget / RAG adequacy (mini-interview if needed)
  ↓
5.7: Load test at 100K + subagent implementation
  ↓
5.8: Documentation finalization
  ↓
Phase 6: Repo-Analysis
```

### 5.1: Flow Redesign (INTERVIEW → IMPLEMENT)

**Status: INTERVIEW COMPLETE — ready for implementation**

#### Interview Questions (6)

1. Confirm: unified flow with 2 entry points (interactive / programmatic). No separate modes. Interview adapts. Validate runs on every flow. Yes/no?
2. Validate → interview loop: full re-pass (interview → decompose → ... → validate) or short-circuit to just affected blocks?
3. Cross-workflow "refactor everything" (UC-MW-13): run the flow once per workflow? Or a separate capability?
4. Mode field in state: replace with context detection (workflow_id/block_id/structured_input presence)? Or keep mode with 2 values (interactive/programmatic)?
5. Export block: keep separate or fold into author/wire/promote (each exports its own artifacts)?
6. Naming: "validate" for the new block? Or "check"/"verify"/something else?

#### Decisions

1. **YES** — Unified flow confirmed. 2 entry points (interactive / programmatic). No separate modes. Interview adapts based on context. Validate runs on every flow.
2. **TIERED HYBRID** — Validate is one block with internal tiered checks, each with its own resolution path and RAG re-querying:
   - Tier 1 (structural, deterministic): auto-fix in place, re-validate. No loop.
   - Tier 2 (quality, LLM-assessed): LLM proposes fix, short-circuits to affected blocks only.
   - Tier 3 (semantic, LLM-powered): escalates to interview → full re-pass (interview → decompose → ... → validate).
   - Single block, multiple internal RAG queries per sub-check — block count doesn't drive RAG precision, query scoping does.
   - Interview adapts to caller: human (interactive) or LLM-as-interviewer (programmatic).
   - Programmatic mode: LLM resolves what it can confidently, fails with explanation on low confidence (consistent with UC-MW-12).
   - New UC-MW-37: Programmatic validation resolution — LLM acts as interviewer, fails on ambiguity.
3. **SPLIT** — Two scopes for optimization:
   - **Automatic (every flow)**: optimize block checks the current workflow for bloat, spaghetti, local DRY during every create/update. Part of the unified flow.
   - **Manual trigger (user-prompted)**: cross-workflow DRY analysis — scanning all workflows for patterns to abstract into shared segments. User prompts this explicitly. HITL required before creating any new shared patterns.
   - No separate audit mode. Local optimization is automatic. Cross-workflow refactoring is on-demand.
4. **DROP MODE** — Remove `mode` field from state. Route uses context detection: `workflow_id` → update, `workflow_id` + `block_id` → refine, `structured_input` → programmatic, neither → build. No redundant flag. **Note:** Meta-workflow agent prompt (`prompts/meta-workflow.md`) needs updating — currently mode-centric.
5. **KEEP SEPARATE** — Export stays as its own block after promote. Single deterministic "flush to disk" step. Session state tracked via OpenMemory so user can resume across kiro sessions (not long-term history — just active create/update sessions). New UC-MW-38: Session persistence — track active workflow design sessions in OpenMemory so user can resume after interruptions (meetings, etc.). LangGraph PG checkpointer handles graph state; OpenMemory tracks session context (what we're doing, where we left off, decisions made).
6. **VALIDATE** — Name confirmed. "validate" for the new pre-promote block.

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

### 5.2: Subagent Design (INTERVIEW → IMPLEMENT)

**Status: INTERVIEW COMPLETE — implementation deferred to 5.6 load test**

Subagent is a general execution pattern (context reset). Decisions here inform how validate and other blocks get executed.

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

11. _(moved to 5.3 — validate-specific, resolved there)_
12. **PER-BLOCK** — One subagent per autonomous block. Each block has its own OPA context; grouping into segments would mix contexts and defeat isolation.
13. **NO SPECIAL CASE** — Programmatic mode runs the same graph. Each autonomous block spawns its own subagent. No HITL interrupts, but subagent-per-block pattern is identical.
14. **DIRECT MCP** — Subagent calls kiro-cortex MCP directly for OPA-scoped instructions. Root doesn't pre-fetch. Fresh context + own RAG query = maximum isolation.

**Overall design: Option B — Generic subagent for context reset.**
- One generic subagent config. Purpose: fresh context window.
- Specialization comes from OPA scoping + task description, not agent config.
- Root agent blocks (HITL): route (inline), interview, research, promote.
- Subagent candidates (autonomous): decompose, optimize, author, wire, validate, export.
- Implemented as `execution_env: "subagent"` flag on BlockDef — toggle per-block without rewiring graph.
- Start inline, flip to subagent as scale demands (validated in 5.6 load test).

### 5.3: Package Restructure (IMPLEMENT)

**Status: IN PROGRESS**

Move agent-specific code into `agents/` directory. kiro-cortex becomes a generic shared library. Agent packages depend on kiro-cortex via `pnpm link:`.

#### What Moves

- `src/meta-workflow/` → `agents/meta-workflow/src/`
- `workflows/meta-workflow/` → `agents/meta-workflow/` (instructions/, workflow.yaml, pipeline.yaml)
- `scripts/render-diagram.ts` → `agents/meta-workflow/scripts/`
- `prompts/meta-workflow.md` → `agents/meta-workflow/prompts/` (if exists)

#### What Stays in kiro-cortex

- `src/opa/`, `src/embedding/`, `src/instruction/`, `src/workflow/` — generic shared lib
- `src/Sql.ts`, `src/mcp.ts`, `src/index.ts`, `src/migrations/` — infrastructure
- `policies/` — shared OPA policies
- `docs/ARCHITECTURE.md` — system-level docs

#### Agent Package Structure

```
agents/meta-workflow/
  src/                    ← block implementations (state, route, interview, etc.)
  instructions/           ← YAML artifacts per block
  workflow.yaml
  pipeline.yaml
  docs/
    architecture.yaml     ← per-workflow arch doc (5.4 validate checks against this)
  scripts/
    render-diagram.ts
  prompts/
    meta-workflow.md
  package.json            ← "kiro-cortex": "link:../.."
  tsconfig.json
```

#### mcp.ts Coupling

`mcp.ts` imports `buildMetaWorkflow` from meta-workflow. For now: update import path to `../agents/meta-workflow/src/graph.js`. Dynamic workflow discovery deferred to Phase 6 when second workflow exists.

### 5.4: Validate Block (INTERVIEW COMPLETE → IMPLEMENT)

**Status: INTERVIEW COMPLETE — ready for implementation**

5.2 complete — subagent decisions (Option B, per-block, direct MCP) inform validate execution.

#### Interview Questions (5)

7. UC-MW-32 (per-workflow arch docs): created during interview? Validate checks against it?
8. UC-MW-33 (semantic gap analysis): is this the validate block, or a sub-step within it?
9. Should validate attempt autonomous fixes or only report? (User said "loop until analysis is complete with option to raise discrepancies")
10. What checks does validate run? Proposed list:
    - Structural completeness (filesystem artifacts, pipeline↔block consistency) — from UC-MW-29
    - Instruction bloat per block (UC-MW-8) — currently in optimize
    - Cross-workflow DRY (UC-MW-10/13) — currently in optimize
    - Scoped re-optimize: can this workflow reuse global patterns? Context budget? (UC-MW-14)
    - Semantic gap: use cases vs implementation coverage (UC-MW-33)
11. Validate as subagent: autonomous loop that can interrupt back to root? Or stays in root agent?

#### Decisions

7. **INTERVIEW → ARCH DOC** — Interview captures architecture doc, stored at `docs/architecture.yaml` in the workflow root. Validate checks implementation against it. Arch doc lives with the agent package (not centrally). Packaging split (kiro-cortex as shared lib, agent packages self-contained) established in 5.3 — validate just needs a workflow root path.
8. **SUB-CHECK INSIDE VALIDATE** — Semantic gap analysis is tier 3 within validate, not a separate block. Validate runs as subagent (Option B), loops through tiers with fresh RAG queries per check. Sequential thinking pattern handles context pressure within the subagent. Returns condensed result to root.
9. **CONFIDENCE-BASED RESOLUTION** — Validate fixes what it's confident about (any tier), re-validates. Low confidence: interactive → raises to interview (HITL), programmatic → fails with explanation (UC-MW-37). Tier distinction is about check type (structural/quality/semantic), not fix aggressiveness. Confidence drives escalation, not tier number.
10. **CHECK LIST CONFIRMED** —
    - Tier 1 (structural): filesystem artifacts exist, pipeline↔block consistency, YAML schema validity
    - Tier 2 (quality): instruction bloat per block (UC-MW-8), local DRY, scoped re-optimize against global patterns (UC-MW-14)
    - Tier 3 (semantic): arch doc use cases vs block coverage (UC-MW-33), cross-workflow DRY (UC-MW-10/13, user-prompted only)
11. **YES, SUBAGENT** — Validate runs as subagent (Option B). Autonomous, multiple RAG queries per check, returns condensed result. Escalation: subagent returns "low confidence on X" → root routes to interview. Poster child for context reset pattern.

#### Implementation (after interview)

- New validate block (refactored from lint-artifacts)
- Update optimize.ts (move cross-workflow checks to validate, keep local checks)
- Wire validate into graph between wire and promote
- Smoke test validate loop

### 5.5: Multi-instruction YAML + Hierarchical Layout (UC-MW-30/31)

**Status: READY (no interview needed, independent of 5.1-5.3)**

Can run in parallel with validate implementation.

- Array of instructions per YAML (each gets own vector in pgvector)
- Directory hierarchy: `instructions/<domain>/<topic>.yaml`
- Seed.ts: recursive directory walk + multi-instruction parsing
- Author block: chunking guidance (one concept per instruction)
- Backward compat with single-instruction files

### 5.6: Context Budget Analysis + RAG Adequacy

**Status: BLOCKED on 5.4 + 5.5**

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

### 5.7: Load/Validation Test at 100K Instructions

**Status: BLOCKED on 5.1-5.6**

- Seed pgvector with ~100K instructions across multiple domains
- Run complex multi-block workflow with mocked HITL
- Validate: OPA scoping at scale, RAG relevance (no context drift), block executor injection, subagent context shedding, context budget adequacy (no silent truncation)
- Goal: prove OPA→RAG pipeline holds at scale before building real workflows

### 5.8: Documentation Finalization

**Status: BLOCKED on 5.1-5.7**

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
src/                          ← generic shared library
  opa/{index,Opa}.ts
  embedding/{index,Embedding}.ts
  instruction/{index,Repo,Loader,Error}.ts
  workflow/{index,Block,Registry,Executor,Pipeline,Workflow}.ts
  Sql.ts, mcp.ts, index.ts (doc-only)
  migrations/{0001_init,0002_add_instruction_columns,0003_add_content_hash,_schema.sql}.ts
agents/
  meta-workflow/              ← agent package ("kiro-cortex": "link:../..")
    src/{state,route,interview,research,decompose,optimize,lint-artifacts,validate,author,wire,promote,export,seed,graph}.ts
    instructions/{route,interview,research,decompose,optimize,author,wire,promote,export,lint-artifacts}.yaml
    workflow.yaml, pipeline.yaml
    docs/architecture.yaml    ← per-workflow arch doc
    scripts/render-diagram.ts
    prompts/meta-workflow.md
    package.json, tsconfig.json
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
1. 5.1 (flow redesign) COMPLETE — all 6 questions answered, code implemented. 34 files, 0 errors.
2. 5.2 (subagent design) COMPLETE — Option B (generic subagent for context reset). Implementation deferred to 5.7 load test.
3. 5.3 (package restructure) IN PROGRESS — move agent-specific code to agents/meta-workflow/, kiro-cortex becomes shared lib.
4. 5.4 (validate block) INTERVIEW COMPLETE — Q7-11 all answered. Ready for implementation after 5.3.
5. 5.5 (multi-instruction YAML) READY — no interview needed, can run parallel with 5.4.
6. New UCs: UC-MW-34 (adaptive interview), UC-MW-35 (tiered validate), UC-MW-36 (validate→interview loop), UC-MW-37 (programmatic validation), UC-MW-38 (session persistence).
7. Agent prompt (`prompts/meta-workflow.md`) needs updating — currently mode-centric.
8. Three bugs in old graph all subsumed by redesign.

Next step: Implement 5.3 (package restructure), then 5.4 (validate) and 5.5 (multi-instruction YAML).
