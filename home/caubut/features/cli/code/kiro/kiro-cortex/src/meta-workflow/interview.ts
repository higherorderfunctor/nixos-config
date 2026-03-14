/**
 * @module meta-workflow/interview
 * Interview block — gathers workflow requirements from the user via HITL interrupt.
 *
 * ARCH: Uses LangGraph interrupt() for human-in-the-loop. The pipeline pauses,
 * the user provides workflow details, and the pipeline resumes with
 * Command({ resume: answer }).
 *
 * ARCH: Sets needs_research flag when the user indicates knowledge gaps.
 * The graph routes interview → research → interview when research is needed,
 * then interview → decompose when requirements are complete.
 */

import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType, BlockSpec } from "./state.js"

/** Shape of the user's interview response. All fields optional for partial updates. */
interface InterviewAnswer {
  readonly workflow_name?: string
  readonly workflow_description?: string
  readonly blocks?: ReadonlyArray<BlockSpec>
  /** Set true to trigger research before decompose (UC-MW-7). */
  readonly needs_research?: boolean
}

/**
 * Interview the user about the workflow they want to build or update.
 * Pauses execution via interrupt() and waits for user input.
 *
 * ARCH: When research_findings are present (from a previous research loop),
 * the interview prompt includes them so the user can refine requirements.
 *
 * @returns Partial state with workflow metadata and needs_research flag.
 */
export function interviewNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  const researchContext = state.research_findings
    ? `\n\nResearch findings from previous step:\n${state.research_findings}`
    : ""

  const question = state.mode === "update"
    ? `Updating workflow "${state.workflow_name}". What changes?${researchContext}\n\nProvide updated details. Set needs_research: true if you need external research first.`
    : state.mode === "audit"
      ? `Optimization findings for review:\n${state.optimization_report}${researchContext}\n\nWhich issues should be addressed? Provide workflow_name and blocks to restructure.`
      : `Describe the workflow: name, description, and optionally blocks.${researchContext}\n\nSet needs_research: true if you want external research before decomposition.`

  const answer: unknown = interrupt({ question })

  // CONSTRAINT: Answer can be a JSON string or pre-parsed object depending on caller
  const parsed: InterviewAnswer = typeof answer === "string"
    ? JSON.parse(answer) as InterviewAnswer
    : answer as InterviewAnswer

  return {
    workflow_name: parsed.workflow_name ?? state.workflow_name,
    workflow_description: parsed.workflow_description ?? state.workflow_description,
    blocks: parsed.blocks ?? state.blocks,
    needs_research: parsed.needs_research ?? false,
  }
}
