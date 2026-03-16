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
  switch (state.mode) {
    case "refine":
      return new Command({ goto: "author" })
    case "audit":
      return new Command({ goto: "gap-analyze" })
    case "programmatic":
      return new Command({ goto: "decompose" })
    default:
      // build, update
      return new Command({ goto: "interview" })
  }
}
