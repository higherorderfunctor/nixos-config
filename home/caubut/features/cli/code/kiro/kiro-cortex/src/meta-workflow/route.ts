/**
 * @module meta-workflow/route
 * Route block — classifies user intent and directs to the appropriate next block.
 *
 * ARCH: Uses LangGraph Command for conditional routing. Supports 5 modes:
 * - build/update → interview (gather requirements)
 * - refine → author (direct instruction editing)
 * - audit → gap-analyze (cross-system completeness check, UC-MW-29, then optimize)
 * - programmatic → decompose (skip interview, UC-MW-4/12)
 */

import { Command } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Route based on workflow mode.
 *
 * ARCH: Returns a LangGraph Command with `goto` for conditional edge routing.
 * Each mode maps to a specific entry block in the pipeline.
 */
export const routeNode = (state: MetaWorkflowStateType): Command => {
  // ARCH: Map workflow_id from caller input to workflow_name used by all downstream nodes.
  const update = state.workflow_id && !state.workflow_name
    ? { workflow_name: state.workflow_id }
    : {}

  switch (state.mode) {
    case "refine":
      return new Command({ goto: "author", update })
    case "audit":
      return new Command({ goto: "gap-analyze", update })
    case "programmatic":
      return new Command({ goto: "decompose", update })
    default:
      // build, update
      return new Command({ goto: "interview", update })
  }
}
