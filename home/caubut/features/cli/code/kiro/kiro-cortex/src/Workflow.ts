import { StateGraph, Annotation, START, END } from "@langchain/langgraph"

const GraphState = Annotation.Root({
  query: Annotation<string>,
  user_id: Annotation<string>,
  policy_decision: Annotation<{ allowed: boolean; reason: string } | null>,
  vector_results: Annotation<any[] | null>,
  context: Annotation<string | null>,
  response: Annotation<string | null>,
})

export const checkPolicy = async (state: typeof GraphState.State) => ({
  policy_decision: {
    allowed: state.user_id !== "",
    reason: state.user_id ? "allowed" : "missing user_id",
  },
})

export const vectorSearch = async (state: typeof GraphState.State) => ({
  vector_results: state.policy_decision?.allowed
    ? [
        { id: "test-1", content: "Test memory 1", score: 0.9 },
        { id: "test-2", content: "Test memory 2", score: 0.8 },
      ]
    : [],
})

export const assembleContext = async (state: typeof GraphState.State) => ({
  context: state.vector_results?.length
    ? state.vector_results.map((r) => `[${r.score}] ${r.content}`).join("\n")
    : null,
})

export const generateResponse = async (state: typeof GraphState.State) => ({
  response: state.policy_decision?.allowed
    ? `Query: ${state.query}\nContext:\n${state.context}\n\nResponse: Test workflow complete`
    : `Policy denied: ${state.policy_decision?.reason || "unknown"}`,
})

export function createTestWorkflow() {
  return new StateGraph(GraphState)
    .addNode("policy", checkPolicy)
    .addNode("vector", vectorSearch)
    .addNode("assemble", assembleContext)
    .addNode("generate", generateResponse)
    .addEdge(START, "policy")
    .addEdge("policy", "vector")
    .addEdge("vector", "assemble")
    .addEdge("assemble", "generate")
    .addEdge("generate", END)
    .compile()
}
