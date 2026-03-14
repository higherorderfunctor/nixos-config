import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

interface InterviewAnswer {
  readonly workflow_name?: string
  readonly workflow_description?: string
  readonly blocks?: ReadonlyArray<{ id: string; name: string; description: string }>
}

export function interviewNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  const answer: unknown = interrupt({
    question: state.mode === "update"
      ? `Updating workflow "${state.workflow_name}". What changes? Provide updated block list if needed.`
      : "Describe the workflow: name, description, and blocks (id, name, description each).",
  })
  const parsed: InterviewAnswer = typeof answer === "string" ? JSON.parse(answer) as InterviewAnswer : answer as InterviewAnswer
  return {
    workflow_name: parsed.workflow_name ?? state.workflow_name,
    workflow_description: parsed.workflow_description ?? state.workflow_description,
    blocks: parsed.blocks ?? state.blocks,
  }
}
