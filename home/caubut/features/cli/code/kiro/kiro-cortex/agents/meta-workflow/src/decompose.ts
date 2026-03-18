/**
 * @module meta-workflow/decompose
 * Decompose block — proposes block structure from interview output.
 *
 * ARCH: Searches BlockRegistry for existing reusable blocks (UC-MW-10),
 * proposes new blocks for uncovered capabilities, and suggests execution
 * environments per block (UC-MW-19). Uses interrupt() for user approval.
 *
 * ARCH: For programmatic calls (UC-MW-4/12), uses structured_input directly
 * without interrupt — the caller already provided the block breakdown.
 * Fails if structured_input is missing required fields (UC-MW-12).
 */

import { Effect } from "effect"
import { interrupt } from "@langchain/langgraph"
import { BlockRegistry } from "kiro-cortex/workflow"
import type { MetaWorkflowStateType, BlockSpec } from "./state.js"

/**
 * Propose block structure for the workflow being designed.
 *
 * - Programmatic: validates structured_input, uses proposed_blocks directly.
 * - Interactive: searches registry for reuse, proposes structure via interrupt().
 *
 * @returns Partial state with blocks and workflow metadata.
 */
export const decomposeNode = async (
  state: MetaWorkflowStateType,
): Promise<Partial<MetaWorkflowStateType>> => {
  // --- Programmatic: use structured_input directly (UC-MW-4/12) ---
  if (state.structured_input) {
    if (!state.structured_input.problem_statement || !state.structured_input.use_cases?.length) {
      return { error: "Programmatic mode requires problem_statement and use_cases (UC-MW-12)" }
    }
    return {
      workflow_description: state.structured_input.problem_statement,
      blocks: state.structured_input.proposed_blocks,
    }
  }

  // --- Search registry for reusable blocks ---
  const registry = await Effect.runPromise(
    Effect.map(BlockRegistry, (r) => r.search(state.workflow_description)).pipe(
      Effect.provide(BlockRegistry.Default),
    ),
  )

  // ARCH: Build a proposal showing existing blocks that could be reused
  // and gaps that need new blocks. The user refines via interrupt().
  const reusable = registry.map((b) => ({
    id: b.id,
    name: b.name,
    description: b.description,
    source: "existing" as const,
  }))

  const proposal = {
    workflow: { name: state.workflow_name, description: state.workflow_description },
    research_context: state.research_findings || "(none)",
    reusable_blocks: reusable,
    current_blocks: state.blocks,
    instructions: [
      "Review the proposed block structure. For each block provide:",
      "  - id, name, description",
      "  - execution_env: inline | subagent | ai-orchestrated (UC-MW-19)",
      "Reuse existing blocks where possible (UC-MW-10).",
      "Return JSON array of BlockSpec objects.",
    ].join("\n"),
  }

  const answer: unknown = interrupt(proposal)

  // CONSTRAINT: Answer is a JSON array of BlockSpec or a JSON string
  const blocks: ReadonlyArray<BlockSpec> = typeof answer === "string"
    ? JSON.parse(answer) as ReadonlyArray<BlockSpec>
    : answer as ReadonlyArray<BlockSpec>

  return { blocks }
}
