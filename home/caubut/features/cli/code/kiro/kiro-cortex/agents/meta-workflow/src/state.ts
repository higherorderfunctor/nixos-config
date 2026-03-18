/**
 * @module meta-workflow/state
 * LangGraph state definition for the meta-workflow pipeline.
 *
 * ARCH: The meta-workflow is the bootstrap workflow that builds, updates, and
 * refines other workflows. It's hand-wired (not via PipelineExecutor) because
 * it needs to exist before the pipeline system can build anything.
 *
 * ARCH: No mode field — routing uses context detection (5.1 decision Q4):
 * - workflow_id present → update
 * - workflow_id + block_id → refine (narrows to specific block)
 * - structured_input present → programmatic (skip interview)
 * - neither → build (fresh start)
 */

import { Annotation } from "@langchain/langgraph"

// ---------------------------------------------------------------------------
// Supporting types
// ---------------------------------------------------------------------------

/** Specification for a single block within a workflow being designed. */
export interface BlockSpec {
  readonly id: string
  readonly name: string
  readonly description: string
  /**
   * Execution environment recommendation (UC-MW-19).
   * - inline: simple transforms, no LLM reasoning needed
   * - subagent: autonomous LLM work with fresh context
   * - ai-orchestrated: interactive, judgment-based sequencing
   */
  readonly execution_env?: "inline" | "subagent" | "ai-orchestrated"
}

/**
 * Structured input for programmatic calls (UC-MW-4, UC-MW-12).
 * Skips interview — caller provides all required context directly.
 *
 * CONSTRAINT: Must include problem_statement AND use_cases or the
 * meta-workflow will fail (UC-MW-12).
 */
export interface StructuredInput {
  readonly problem_statement: string
  readonly use_cases: ReadonlyArray<string>
  readonly proposed_blocks: ReadonlyArray<BlockSpec>
}

// ---------------------------------------------------------------------------
// State annotation
// ---------------------------------------------------------------------------

/**
 * LangGraph state annotation for the meta-workflow.
 *
 * ARCH: This state flows through all blocks. Fields are accumulated as the
 * pipeline progresses — each block reads what it needs and writes its outputs.
 *
 * ARCH: Context detection replaces mode field (5.1 Q4). Route inspects
 * workflow_id, block_id, and structured_input to determine entry point.
 */
export const MetaWorkflowState = Annotation.Root({
  // --- Core fields ---

  /** Workflow ID from caller input (mapped to workflow_name by route). */
  workflow_id: Annotation<string>,
  /** Specific block to refine — narrows interview to this block (UC-MW-34). */
  block_id: Annotation<string>,
  /** Name of the workflow being designed (used as directory name). */
  workflow_name: Annotation<string>,
  /** Human-readable description of the workflow's purpose. */
  workflow_description: Annotation<string>,
  /** Block specifications — set by interview (manual) or decompose (proposed). */
  blocks: Annotation<ReadonlyArray<BlockSpec>>,
  /** Authored instruction text per block ID (output of author block). */
  instructions: Annotation<Record<string, string>>,
  /** Generated pipeline YAML (output of wire block). */
  pipeline_yaml: Annotation<string>,
  /** Error message if any block fails. */
  error: Annotation<string | null>,

  // --- Research fields ---

  /** Accumulated research findings from external search. */
  research_findings: Annotation<string>,
  /** Whether interview wants research before proceeding. */
  needs_research: Annotation<boolean>,

  // --- Decompose / optimize fields ---

  /** Optimization report — issues found by optimize block. */
  optimization_report: Annotation<string>,
  /** Whether optimize recommends redesign (loops back to decompose). */
  needs_redesign: Annotation<boolean>,

  // --- Trigger selection (UC-MW-26) ---

  /** How the workflow will be triggered: dedicated agent or skill. */
  trigger_type: Annotation<"agent" | "skill" | null>,

  // --- Promote fields ---

  /** File paths of generated trigger artifacts (SKILL.md, agent config). */
  promoted_artifacts: Annotation<ReadonlyArray<string>>,

  // --- Programmatic mode (UC-MW-4/12) ---

  /** Structured input for programmatic calls — skips interview. */
  structured_input: Annotation<StructuredInput | null>,
})

/** TypeScript type for the meta-workflow state. */
export type MetaWorkflowStateType = typeof MetaWorkflowState.State
