/**
 * @module meta-workflow/research
 * Research block — gathers external knowledge to inform workflow design.
 *
 * ARCH: Uses interrupt() to pause and present a research prompt. The user
 * (or Claude in kiro-cli) performs the actual search and provides findings.
 * This keeps kiro-cortex free of external search clients — research happens
 * at the CLI layer where all search tools are available.
 *
 * ARCH: Pass-through when needs_research is false. This allows the graph to
 * always route interview → research → decompose without conditional edges
 * for the common case.
 */

import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Gather external research if the interview flagged knowledge gaps.
 *
 * When needs_research is true: interrupt() with a research prompt derived
 * from the workflow description. User provides findings, stored in state.
 *
 * When needs_research is false: pass-through (no-op).
 *
 * @returns Partial state with research_findings and needs_research reset.
 */
export function researchNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  if (!state.needs_research) return {}

  // ARCH: interrupt() pauses the pipeline. The research prompt includes
  // workflow context so the user/Claude knows what to search for.
  const findings: unknown = interrupt({
    question: [
      `Research needed for workflow "${state.workflow_name}":`,
      state.workflow_description,
      "",
      "Please research best practices, similar systems, and prior art.",
      "Provide findings as text (patterns, recommendations, relevant examples).",
    ].join("\n"),
  })

  return {
    research_findings: typeof findings === "string" ? findings : JSON.stringify(findings),
    needs_research: false,
  }
}
