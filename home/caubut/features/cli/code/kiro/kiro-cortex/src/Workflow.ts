import { StateGraph, Annotation, START, END } from "@langchain/langgraph"

const GraphState = Annotation.Root({
  query: Annotation<string>,
  user_id: Annotation<string>,
  agent_role: Annotation<string>,
  task_type: Annotation<string>,
  domain: Annotation<string>,
  token_budget: Annotation<number>,
  policy_decision: Annotation<{ allowed: boolean; reason: string } | null>,
  instructions: Annotation<Array<{ id: string; text: string; priority: string | null; distance: number }> | null>,
  assembled_context: Annotation<string | null>,
  token_count: Annotation<number>,
})

export type ContextState = typeof GraphState.State

export const checkPolicy = async (state: ContextState) => ({
  policy_decision: {
    allowed: state.user_id !== "",
    reason: state.user_id ? "allowed" : "missing user_id",
  },
})

export const vectorSearch = async (_state: ContextState) => ({})

export const assembleContext = async (state: ContextState) => {
  if (!state.instructions?.length) return { assembled_context: null, token_count: 0 }

  const budget = state.token_budget || 4000
  const charBudget = budget * 4
  let assembled = ""
  let included = 0

  for (const inst of state.instructions) {
    const entry = `[${inst.priority || "medium"}] ${inst.text}\n\n`
    if (assembled.length + entry.length > charBudget) break
    assembled += entry
    included++
  }

  return {
    assembled_context: assembled || null,
    token_count: Math.ceil(assembled.length / 4),
  }
}

export const generateResponse = async (_state: ContextState) => ({})

export function createContextWorkflow() {
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
