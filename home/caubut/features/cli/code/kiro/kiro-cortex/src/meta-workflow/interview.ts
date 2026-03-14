/**
 * @module meta-workflow/interview
 * Interview block — gathers workflow requirements from the user via HITL interrupt.
 *
 * ARCH: Uses LangGraph interrupt() for human-in-the-loop. The pipeline pauses,
 * the user provides workflow details (name, description, blocks), and the pipeline
 * resumes with Command({ resume: answer }).
 */

import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/** Shape of the user's interview response. All fields optional for partial updates. */
interface InterviewAnswer {
  readonly workflow_name?: string
  readonly workflow_description?: string
  readonly blocks?: ReadonlyArray<{ id: string; name: string; description: string }>
}

/**
 * Interview the user about the workflow they want to build or update.
 * Pauses execution via interrupt() and waits for user input.
 *
 * @returns Partial state update with workflow name, description, and block specs.
 */
export function interviewNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  // ARCH: interrupt() pauses the LangGraph pipeline. The caller resumes with
  // Command({ resume: jsonAnswer }) via the /workflows/:id/invoke endpoint.
  const answer: unknown = interrupt({
    question: state.mode === "update"
      ? `Updating workflow "${state.workflow_name}". What changes? Provide updated block list if needed.`
      : "Describe the workflow: name, description, and blocks (id, name, description each).",
  })

  // CONSTRAINT: Answer can be a JSON string or pre-parsed object depending on caller
  const parsed: InterviewAnswer = typeof answer === "string"
    ? JSON.parse(answer) as InterviewAnswer
    : answer as InterviewAnswer

  return {
    workflow_name: parsed.workflow_name ?? state.workflow_name,
    workflow_description: parsed.workflow_description ?? state.workflow_description,
    blocks: parsed.blocks ?? state.blocks,
  }
}
