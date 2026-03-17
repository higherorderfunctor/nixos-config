/**
 * @module meta-workflow/graph
 * Hand-wired LangGraph StateGraph for the meta-workflow.
 *
 * ARCH: This is the bootstrap workflow — it must exist before the pipeline system
 * can build anything. Unlike other workflows that use PipelineExecutor + BlockExecutor,
 * this one is hand-wired with explicit node registration and conditional edges.
 *
 * ARCH: Full 4.5 graph with loops:
 * - interview ↔ research (research informs interview, interview may trigger more)
 * - decompose → optimize → author (optimize can recommend redesign via HITL)
 *
 * Graph structure (by mode):
 *   BUILD/UPDATE: route → interview → research → decompose → optimize → author → wire → promote → export → END
 *   REFINE:       route → author → END
 *   AUDIT:        route → lint-artifacts → optimize → interview → research → decompose → optimize → author → wire → promote → export → END
 *   PROGRAMMATIC: route → decompose → optimize → author → wire → promote → export → END
 *
 * ARCH: export node (UC-MW-16/17) writes workflow.yaml metadata to disk for Nix reproducibility.
 * Together with author (instructions/*.yaml) and wire (pipeline.yaml), workflows are fully
 * reconstructable from files. seed.ts provides the inverse: YAML → data for DB insertion.
 */

import { StateGraph, START, END } from "@langchain/langgraph"
import { getCheckpointer } from "../workflow/index.js"
import { MetaWorkflowState, type MetaWorkflowStateType } from "./state.js"
import { routeNode } from "./route.js"
import { interviewNode } from "./interview.js"
import { researchNode } from "./research.js"
import { decomposeNode } from "./decompose.js"
import { optimizeNode } from "./optimize.js"
import { authorNode } from "./author.js"
import { wireNode } from "./wire.js"
import { promoteNode } from "./promote.js"
import { exportNode } from "./export.js"
import { lintArtifactsNode } from "./lint-artifacts.js"

/**
 * Build the meta-workflow StateGraph with PG checkpointer.
 *
 * ARCH: route uses Command with goto for mode-based entry point selection.
 * Conditional edges handle the interview↔research and optimize→author/decompose loops.
 */
export const buildMetaWorkflow = async () => {
  const checkpointer = await getCheckpointer()

  const graph = new StateGraph(MetaWorkflowState)
    // --- Nodes ---
    .addNode("route", routeNode, { ends: ["interview", "author", "lint-artifacts", "decompose"] })
    .addNode("lint-artifacts", lintArtifactsNode)
    .addNode("interview", interviewNode)
    .addNode("research", researchNode)
    .addNode("decompose", decomposeNode)
    .addNode("optimize", optimizeNode)
    .addNode("author", authorNode)
    .addNode("wire", wireNode)
    .addNode("promote", promoteNode)
    .addNode("export", exportNode)

    // --- Entry ---
    .addEdge(START, "route")

    // --- interview ↔ research loop ---
    // ARCH: After interview, check needs_research. If true → research → back to interview.
    // If false → decompose.
    .addConditionalEdges("interview", (s: MetaWorkflowStateType) =>
      s.needs_research ? "research" : "decompose",
    )
    .addEdge("research", "interview")

    // --- lint-artifacts → optimize (audit mode entry, UC-MW-29) ---
    .addEdge("lint-artifacts", "optimize")

    // --- decompose → optimize → author (with redesign loop) ---
    .addEdge("decompose", "optimize")
    // ARCH: optimize routing depends on scope:
    // - Audit mode (UC-MW-13): global scan → interview to discuss findings with user
    // - Build/update/programmatic: local check → redesign loop or author
    .addConditionalEdges("optimize", (s: MetaWorkflowStateType) =>
      s.mode === "audit" && !s.needs_redesign ? "interview"
        : s.needs_redesign ? "decompose"
        : "author",
    )

    // --- author → wire or END (refine skips wire) ---
    .addConditionalEdges("author", (s: MetaWorkflowStateType) =>
      s.mode === "refine" ? END : "wire",
    )

    // --- wire → promote → export → END ---
    .addEdge("wire", "promote")
    .addEdge("promote", "export")
    .addEdge("export", END)

  return graph.compile({ checkpointer })
}
