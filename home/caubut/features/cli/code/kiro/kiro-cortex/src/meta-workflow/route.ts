/**
 * @module meta-workflow/route
 * Route block — classifies user intent and directs to the appropriate next block.
 *
 * ARCH: Uses LangGraph Command for conditional routing. Refine mode skips
 * interview (user already knows which block to improve) and goes directly
 * to author. Build/update modes go through interview first.
 */

import { Command } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Route based on workflow mode: refine → author, build/update → interview.
 * ARCH: Returns a LangGraph Command with `goto` for conditional edge routing.
 */
export const routeNode = (state: MetaWorkflowStateType): Command =>
  new Command({ goto: state.mode === "refine" ? "author" : "interview" })
