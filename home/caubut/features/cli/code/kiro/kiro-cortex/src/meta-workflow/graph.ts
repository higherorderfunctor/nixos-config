import { StateGraph, START, END } from "@langchain/langgraph"
import { getCheckpointer } from "../PipelineExecutor.js"
import { MetaWorkflowState, type MetaWorkflowStateType } from "./state.js"
import { routeNode } from "./route.js"
import { interviewNode } from "./interview.js"
import { authorNode } from "./author.js"
import { wireNode } from "./wire.js"

export const buildMetaWorkflow = async () => {
  const checkpointer = await getCheckpointer()

  const graph = new StateGraph(MetaWorkflowState)
    .addNode("route", routeNode, { ends: ["interview", "author"] })
    .addNode("interview", interviewNode)
    .addNode("author", authorNode)
    .addNode("wire", wireNode)
    .addEdge(START, "route")
    .addEdge("interview", "author")
    .addConditionalEdges("author", (state: MetaWorkflowStateType) =>
      state.mode === "refine" ? END : "wire",
    )
    .addEdge("wire", END)

  return graph.compile({ checkpointer })
}
