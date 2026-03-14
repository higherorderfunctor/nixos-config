/**
 * @module meta-workflow/state
 * LangGraph state definition for the meta-workflow pipeline.
 *
 * ARCH: The meta-workflow is the bootstrap workflow that builds, updates, and
 * refines other workflows. It's hand-wired (not via PipelineExecutor) because
 * it needs to exist before the pipeline system can build anything.
 */

import { Annotation } from "@langchain/langgraph"

/** Specification for a single block within a workflow being designed. */
export interface BlockSpec {
  readonly id: string
  readonly name: string
  readonly description: string
}

/**
 * LangGraph state annotation for the meta-workflow.
 *
 * ARCH: This state flows through all 4 blocks (route → interview → author → wire).
 * The `instructions` field holds authored instruction text per block ID — this is
 * the OUTPUT of the author block, not the OPA-injected `_context`.
 */
export const MetaWorkflowState = Annotation.Root({
  /** Workflow operation mode: build new, update existing, or refine instructions. */
  mode: Annotation<"build" | "update" | "refine">,
  /** Name of the workflow being designed (used as directory name). */
  workflow_name: Annotation<string>,
  /** Human-readable description of the workflow's purpose. */
  workflow_description: Annotation<string>,
  /** Block specifications gathered during interview. */
  blocks: Annotation<ReadonlyArray<BlockSpec>>,
  /** Authored instruction text per block ID (output of author block). */
  instructions: Annotation<Record<string, string>>,
  /** Generated pipeline YAML (output of wire block). */
  pipeline_yaml: Annotation<string>,
  /** Error message if any block fails. */
  error: Annotation<string | null>,
})

/** TypeScript type for the meta-workflow state. */
export type MetaWorkflowStateType = typeof MetaWorkflowState.State
