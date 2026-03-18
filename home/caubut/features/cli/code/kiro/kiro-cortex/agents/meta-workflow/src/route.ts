/**
 * @module meta-workflow/route
 * Route block — classifies user intent via context detection and directs to
 * the appropriate next block.
 *
 * ARCH: No mode field (5.1 Q4). Uses context detection:
 * - structured_input present → decompose (programmatic, UC-MW-4/12)
 * - workflow_id present → interview (update/refine — interview adapts, UC-MW-34)
 * - neither → interview (build — fresh start)
 */

import { Command } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Route based on state context.
 *
 * ARCH: Returns a LangGraph Command with `goto` for conditional edge routing.
 * Context detection replaces the old mode switch (5.1 Q4).
 */
export const routeNode = (state: MetaWorkflowStateType): Command => {
  // ARCH: Map workflow_id from caller input to workflow_name used by all downstream nodes.
  const update: Partial<MetaWorkflowStateType> = state.workflow_id && !state.workflow_name
    ? { workflow_name: state.workflow_id }
    : {}

  // Programmatic: structured_input provided → skip interview (UC-MW-4/12)
  if (state.structured_input) {
    return new Command({ goto: "decompose", update })
  }

  // Interactive: interview adapts based on workflow_id / block_id presence (UC-MW-34)
  return new Command({ goto: "interview", update })
}
