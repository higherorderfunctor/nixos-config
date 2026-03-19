# kiro-cortex Resume — 2026-03-19

## What Is This Project

kiro-cortex is a workflow orchestration platform that replaces steering files with structured instructions stored in PostgreSQL/pgvector, governed by OPA policies, and orchestrated via the **segment model**: workflows are composed of deterministic LangGraph segments stitched by Claude orchestration at AI boundaries.

## Current State

Branch: chore/save-point
Phase 4.5+ COMPLETE. UC-MW-29 DONE. 34 files, 0 errors, 0 warnings.
Validation checklist: **9/9 complete** — all 5 smoke tests pass.

**5.1–5.7 COMPLETE. Phase 6: Dungeon Crawler Test Harness via meta-workflow is NEXT.**

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
5.7: MVP gap fixes (interrupt surfacing, output paths, author metadata)
  ↓
5.8: Documentation finalization
  ↓
Phase 6: Dungeon Crawler Test Harness (via meta-workflow)
  ↓
Phase 7: Repo-Analysis
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
5. **KEEP SEPARATE** — Export stays as its own block after promote. Single deterministic "flush to disk" step. Session state tracked via OpenMemory so user can resume across kiro sessions (not long-term history — just active create/update sessions). New UC-MW-38: Session persistence — system-level requirement for ALL workflows. On interrupt, agent stores thread_id + workflow_id + context in OpenMemory. On spawn, agent queries for resumable sessions. LangGraph PG checkpointer handles graph state; OpenMemory tracks session context (what we're doing, where we left off, decisions made).
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

**Status: COMPLETE**

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

**Status: COMPLETE**

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

**Status: COMPLETE**

Can run in parallel with validate implementation.

- Array of instructions per YAML (each gets own vector in pgvector)
- Directory hierarchy: `instructions/<domain>/<topic>.yaml`
- Seed.ts: recursive directory walk + multi-instruction parsing
- Author block: chunking guidance (one concept per instruction)
- Backward compat with single-instruction files

### 5.6: Context Budget Analysis + RAG Adequacy (INTERVIEW → IMPLEMENT)

**Status: COMPLETE**

#### Interview Questions (6, collapsed to 3 decisions)

15. How does the system detect when relevant instructions got dropped?
16. Should blocks declare a context budget?
17. Should the executor support multi-query RAG?
18. Should there be a cosine distance cutoff?
19. How do validate/optimize use context budget info?
20. At 100K+ instructions, what's the layered strategy?

#### Decisions

**Q15-Q18 (combined): Adaptive multi-query with distance-based sizing.**
- Surface cosine distances from pgvector (already computed, just not exposed).
- Cosine distance cutoff for dynamic sizing — stop returning results when they become
  irrelevant. No fixed result count. Blocks get exactly as many relevant instructions as exist.
- OPA `max_results` repurposed as ceiling (safety cap), not target.
- Multi-query built before load test so 5.7 validates the real design.
- No per-block declared budgets (neither BlockDef nor OPA per-block overrides).
  Budgets are a crutch — adaptive retrieval makes them unnecessary.

**Q19: Two-layer retrieval (Option C).**
- Executor layer: fast single pass — embed `block.description`, search with distance cutoff,
  return results. This is the baseline for inline blocks.
- Subagent layer: iterative fold via MCP — subagent queries kiro-cortex, reads results,
  reasons about gaps (sequential thinking), queries again with refined terms. Accumulates
  until new results are below distance threshold. Like a fold function over queries.
- Validate tier 2: flags when executor single pass hits OPA ceiling (truncation risk).
  Signal that block should consider `execution_env: "subagent"` for iterative retrieval.
- Optimize: flags low-overlap multi-query results as "block too broad, consider splitting."

**Q20: Layered strategy at 100K+ confirmed.**
1. OPA domain filtering — coarse filter, narrows search space (exists)
2. Cosine distance cutoff — dynamic sizing, stops returning garbage (new)
3. OPA ceiling — safety cap, prevents runaway context (existing max_results repurposed)
4. Subagent iterative fold — intelligent multi-query for complex blocks via MCP (new)
5. Validate quality gate — flags ceiling hits, recommends execution_env upgrades (new)
Load test (5.7) validates this stack end-to-end at 100K.

#### Implementation

- ✅ `InstructionRepo.search()` already returns distances (Instruction.distance field)
- ✅ Cosine distance cutoff in `Executor.ts` (COSINE_DISTANCE_CUTOFF = 0.5, tune in 5.7)
- ✅ OPA `max_results` as ceiling — executor fetches up to ceiling, filters by distance
- ✅ `ContextMeta` type: ceiling_hit, count, dropped — injected as `_context_meta`
- Subagent iterative fold: deferred to 5.7 (requires execution_env implementation)

### 5.7: MVP Gap Fixes (manual, pre-meta-workflow)

**Status: COMPLETE**

Minimum changes so meta-workflow can attempt to build a new workflow (the dungeon crawler).

#### 5.7.1: Surface interrupt payloads in `run_workflow` response (DONE)

Uses `isInterrupted()` + `INTERRUPT` symbol from LangGraph. Response now returns
`{ thread_id, state, interrupts }` where `interrupts` is array of interrupt values.

#### 5.7.2: Fix output paths → `agents/<name>/` (DONE)

Author, wire, export blocks write to `agents/<name>/`. Export scaffolds `src/`, `docs/`,
`instructions/` subdirectories.

#### 5.7.3: Fix author metadata — derive from state, not hardcoded (DONE)

Added `domain` and `agent_role` fields to `MetaWorkflowState`. Interview captures them.
Author uses state values (defaults: domain from workflow_name, agent_role "workflow-builder").

#### 5.7.4: Update stale instruction YAMLs (DONE)

All 10 instruction YAMLs updated to match Phase 5 redesign:
- Route: context detection replaces mode-based routing
- Interview: adaptive behavior per UC-MW-34, captures domain/agent_role
- Author/wire/export: paths → `agents/{name}/`, state-derived metadata
- Optimize: audit mode reference removed, scope clarified
- Decompose: context-based language replaces mode references
- Validate: new YAML for tiered autonomous loop (UC-MW-35)
- Lint-artifacts: removed (logic moved into validate)

#### 5.7.5: Codify conventions as instructions (DONE)

Extracted from ARCHITECTURE.md into multi-instruction YAMLs:
- `conventions/effect-patterns.yaml`: services, schema, generators (3 instructions)
- `conventions/coding-standards.yaml`: comments, code org, LangGraph blocks (3 instructions)
Domain: `conventions`, accessible to all agent roles via OPA.

#### Gap Analysis (found during dungeon crawler planning)

| Gap | Severity | Fix in 5.7? | Notes |
|-----|----------|-------------|-------|
| Interrupt payloads invisible to Claude | 🔴 Critical | Yes (5.7.1) | Blocks all 5 HITL blocks |
| Output paths wrong (`workflows/` not `agents/`) | 🔴 Critical | Yes (5.7.2) | Wrong directory structure |
| Author metadata hardcoded to "meta" | 🔴 Critical | Yes (5.7.3) | OPA scoping breaks for new workflows |
| Author generates trivial instructions | 🟡 Important | Partial | Claude writes real instructions directly for now |
| Wire only supports linear pipelines | 🟡 Important | No | Dungeon crawler graph.ts hand-wired like meta-workflow |
| No OPA policy generation for new domains | 🟡 Important | No | Manual for now |
| No TypeScript code generation | 🟡 Important | No | Claude writes code directly, meta-workflow handles YAML/config |
| No package scaffolding (package.json etc) | 🟡 Important | No | Claude creates directly |
| Stale instruction YAMLs | 🟢 Nice-to-have | Yes (5.7.4) | Route YAML references modes |
| Subagent execution_env not implemented | 🟢 Defer | No | All blocks run inline for now |
| Session persistence (UC-MW-38) | 🟢 Defer | No | Thread ID + OpenMemory for now |
| Loader embeds before hash check | 🟢 Defer | No | Skip Ollama call when content_hash matches — matters at 100K+ (Phase 6.7) |

### 5.8: Documentation Finalization

**Status: BLOCKED on Phase 6 completion**

- Per-package ARCHITECTURE.md, README.md, USECASES.md
- Stale content cleanup in docs/ARCHITECTURE.md
- Sequence diagram: updated for unified flow + validate loop
- Resume: final state for Phase 7 handoff

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

## Phase 6 — Dungeon Crawler Test Harness (first workflow built by meta-workflow)

**Status: READY — 5.7 complete**

Procedural Myst-style dungeon crawler that validates the full OPA→RAG→LangGraph pipeline at scale.
Design doc: `agents/dungeon-crawler/docs/design.md`. This replaces the old synthetic load test —
the dungeon IS the load test (100K+ facts, OPA domain scoping, multi-block loops, HITL).

### Approach

Use meta-workflow to design and build the dungeon crawler workflow. This test-drives meta-workflow
itself. Gaps found during the build become self-updates to meta-workflow's instructions.

### Steps

```
6.1: Design interview (meta-workflow: route → interview)
  ↓
6.2: Decompose + optimize (meta-workflow: decompose → optimize)
  ↓
6.3: Author + wire + validate + promote + export (meta-workflow completes)
  ↓  ← expect failures here — find gaps
6.4: Fix gaps found in 6.3 (manual), update meta-workflow instructions
  ↓
6.5: Write dungeon crawler code (manual, Claude-assisted)
     - state.ts, graph.ts, block implementations, generator, verifier
  ↓
6.6: OPA policies for dungeon domain
  ↓
6.7: Seed + run at scale (100 → 100K facts), tune COSINE_DISTANCE_CUTOFF
  ↓
6.8: Visualization (optional — WebSocket event bus + web UI, DCC narrator)
```

### What Meta-Workflow Handles vs Manual

| Artifact | Who | Notes |
|----------|-----|-------|
| Instruction YAMLs | Meta-workflow (author) | Per-block instructions |
| pipeline.yaml | Meta-workflow (wire) | Block ordering |
| workflow.yaml | Meta-workflow (export) | Metadata |
| Agent config JSON | Meta-workflow (promote) | Trigger artifact |
| TypeScript code | Claude (manual) | graph.ts, state.ts, blocks, generator, verifier |
| OPA policies | Claude (manual) | dungeon domain in scoping.rego |
| package.json, tsconfig | Claude (manual) | Package scaffolding |

### Cleanup Items (deferred, tracked)

- Block runner agent: clarify if subagent of itself or special agent
- Per-package ARCHITECTURE.md, README.md, USECASES.md
- Stale/deprecated content cleanup in docs/ARCHITECTURE.md
- Comment conventions (ARCH/CONSTRAINT/EXTERNAL) in generated code

## Phase 7 — Repo-Analysis (after Phase 6)

First *real* workflow built by meta-workflow (dungeon crawler was the test harness):
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
    instructions/{route,interview,research,decompose,optimize,author,wire,validate,promote,export}.yaml
    instructions/conventions/{effect-patterns,coding-standards}.yaml
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

Read resume.md. Phase 5 COMPLETE. Phase 6 (Dungeon Crawler Test Harness) is NEXT.

Key context:
1. 5.1-5.7 ALL COMPLETE — flow redesign, subagent design, package restructure, validate block, multi-instruction YAML, context budget, MVP gap fixes.
2. Subagent design: Option B (generic subagent for context reset). Implementation deferred — all blocks run inline for now.
3. Package structure: agents/meta-workflow/ is self-contained, kiro-cortex is shared lib with startMcpServer() factory.
4. Validate block: tier 1 structural checks live, tier 2/3 stubs, conditional edge (validate → promote or validate → interview).
5. Context budget: COSINE_DISTANCE_CUTOFF=0.5, OPA max_results as ceiling, ContextMeta injected as _context_meta.
6. MVP gap fixes: interrupt payloads surfaced (5.7.1), output paths fixed (5.7.2), author metadata from state (5.7.3), stale YAMLs updated (5.7.4), conventions codified (5.7.5).
7. New UCs: UC-MW-34 through UC-MW-38 (adaptive interview, tiered validate, validate→interview loop, programmatic validation, session persistence).
8. Entry point: `bun agents/meta-workflow/src/main.ts`.

Next step: Phase 6 — use meta-workflow to design and build the dungeon crawler workflow. Design doc at `agents/dungeon-crawler/docs/design.md`. This test-drives meta-workflow itself. Start with 6.1 (design interview via run_workflow).
