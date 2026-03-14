/**
 * @module meta-workflow/graph
 * Hand-wired LangGraph StateGraph for the meta-workflow.
 *
 * ARCH: This is the bootstrap workflow — it must exist before the pipeline system
 * can build anything. Unlike other workflows that use PipelineExecutor + BlockExecutor,
 * this one is hand-wired with explicit node registration and conditional edges.
 *
 * ARCH: The meta-workflow does NOT go through the block executor yet. It uses
 * direct node functions. Wiring it through BlockExecutor (so it consumes its own
 * OPA-scoped instructions) is a future step once the system is self-hosting.
 */

import { StateGraph, START, END } from "@langchain/langgraph"
import { getCheckpointer } from "../workflow/index.js"
import { MetaWorkflowState, type MetaWorkflowStateType } from "./state.js"
import { routeNode } from "./route.js"
import { interviewNode } from "./interview.js"
import { authorNode } from "./author.js"
import { wireNode } from "./wire.js"

/**
 * Build the meta-workflow StateGraph with PG checkpointer.
 *
 * Graph structure:
 * ```
 * START → route ──→ interview → author ──→ wire → END
 *                └→ author (refine) ──→ END (if refine mode)
 * ```
 *
 * ARCH: route uses conditional edges (Command with goto). Author conditionally
 * routes to wire or END based on mode (refine skips wire).
 */
export const buildMetaWorkflow = async () => {
  const checkpointer = await getCheckpointer()

  const graph = new StateGraph(MetaWorkflowState)
    .addNode("route", routeNode, { ends: ["interview", "author"] })
    .addNode("interview", interviewNode)
    .addNode("author", authorNode)
    .addNode("wire", wireNode)
    .addEdge(START, "route")
    .addEdge("interview", "author")
    // ARCH: Refine mode skips wire (only updates instructions, not pipeline structure)
    .addConditionalEdges("author", (state: MetaWorkflowStateType) =>
      state.mode === "refine" ? END : "wire",
    )
    .addEdge("wire", END)

  return graph.compile({ checkpointer })
}
