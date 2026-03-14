import { Annotation } from "@langchain/langgraph"

export interface BlockSpec {
  readonly id: string
  readonly name: string
  readonly description: string
}

export const MetaWorkflowState = Annotation.Root({
  mode: Annotation<"build" | "update" | "refine">,
  workflow_name: Annotation<string>,
  workflow_description: Annotation<string>,
  blocks: Annotation<ReadonlyArray<BlockSpec>>,
  instructions: Annotation<Record<string, string>>,
  pipeline_yaml: Annotation<string>,
  error: Annotation<string | null>,
})

export type MetaWorkflowStateType = typeof MetaWorkflowState.State
