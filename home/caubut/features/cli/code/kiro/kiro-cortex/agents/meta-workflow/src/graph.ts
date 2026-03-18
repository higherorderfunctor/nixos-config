/**
 * @module meta-workflow/graph
 * Hand-wired LangGraph StateGraph for the meta-workflow.
 *
 * ARCH: This is the bootstrap workflow — it must exist before the pipeline system
 * can build anything. Unlike other workflows that use PipelineExecutor + BlockExecutor,
 * this one is hand-wired with explicit node registration and conditional edges.
 *
 * ARCH: Unified flow (5.1 decisions). No mode field — context detection in route.
 *
 * Graph structure:
 *   INTERACTIVE:  route → interview ↔ research → decompose → optimize → author → wire → validate → promote → export → END
 *   PROGRAMMATIC: route → decompose → optimize → author → wire → validate → promote → export → END
 *
 * Loops:
 *   interview ↔ research — research informs interview, interview may trigger more
 *   decompose ↔ optimize — optimize can recommend redesign via HITL
 *   validate → promote (clean) or validate → interview (tier 3 discrepancies, wired in 5.2)
 *
 * ARCH: export node (UC-MW-16/17) writes workflow.yaml metadata to disk for Nix reproducibility.
 * Together with author (instructions/*.yaml) and wire (pipeline.yaml), workflows are fully
 * reconstructable from files. seed.ts provides the inverse: YAML → data for DB insertion.
 */

import { StateGraph, START, END } from "@langchain/langgraph"
import { getCheckpointer } from "kiro-cortex/workflow"
import { MetaWorkflowState, type MetaWorkflowStateType } from "./state.js"
import { routeNode } from "./route.js"
import { interviewNode } from "./interview.js"
import { researchNode } from "./research.js"
import { decomposeNode } from "./decompose.js"
import { optimizeNode } from "./optimize.js"
import { authorNode } from "./author.js"
import { wireNode } from "./wire.js"
import { validateNode } from "./validate.js"
import { promoteNode } from "./promote.js"
import { exportNode } from "./export.js"

/**
 * Build the meta-workflow StateGraph with PG checkpointer.
 *
 * ARCH: Unified flow — route uses Command with goto for context-based entry
 * point selection (5.1 Q4). No mode-based branching.
 */
export const buildMetaWorkflow = async () => {
  const checkpointer = await getCheckpointer()

  const graph = new StateGraph(MetaWorkflowState)
    // --- Nodes ---
    .addNode("route", routeNode, { ends: ["interview", "decompose"] })
    .addNode("interview", interviewNode)
    .addNode("research", researchNode)
    .addNode("decompose", decomposeNode)
    .addNode("optimize", optimizeNode)
    .addNode("author", authorNode)
    .addNode("wire", wireNode)
    .addNode("validate", validateNode)
    .addNode("promote", promoteNode)
    .addNode("export", exportNode)

    // --- Entry ---
    .addEdge(START, "route")

    // --- interview ↔ research loop ---
    .addConditionalEdges("interview", (s: MetaWorkflowStateType) =>
      s.needs_research ? "research" : "decompose",
    )
    .addEdge("research", "interview")

    // --- decompose → optimize (with redesign loop) ---
    .addEdge("decompose", "optimize")
    .addConditionalEdges("optimize", (s: MetaWorkflowStateType) =>
      s.needs_redesign ? "decompose" : "author",
    )

    // --- author → wire → validate → promote → export → END ---
    .addEdge("author", "wire")
    .addEdge("wire", "validate")
    // ARCH: validate → promote for now. 5.2 adds conditional edge:
    // validate → interview (tier 3 discrepancies) or validate → promote (clean)
    .addEdge("validate", "promote")
    .addEdge("promote", "export")
    .addEdge("export", END)

  return graph.compile({ checkpointer })
}
