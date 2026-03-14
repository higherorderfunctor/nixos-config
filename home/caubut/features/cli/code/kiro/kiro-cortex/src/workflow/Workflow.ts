/**
 * @module Workflow
 * Phase 3 context assembly workflow — the original RAG pipeline.
 *
 * ARCH: This is the core RAG loop from Phase 3: policy check → vector search →
 * context assembly → response generation. It predates the block/pipeline model
 * (Phase 4) and is used by the /context endpoint directly.
 *
 * ARCH: Will eventually be refactored into a pipeline definition using the
 * block model, but currently serves as the working context assembly engine.
 */

import { StateGraph, Annotation, START, END } from "@langchain/langgraph"

/** LangGraph state annotation for the context assembly workflow. */
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

/** TypeScript type for the context workflow state. */
export type ContextState = typeof GraphState.State

/** Check if the user is allowed to query (basic user_id presence check). */
export const checkPolicy = async (state: ContextState) => ({
  policy_decision: {
    allowed: state.user_id !== "",
    reason: state.user_id ? "allowed" : "missing user_id",
  },
})

/** Placeholder for vector search — actual search happens in the /context handler. */
export const vectorSearch = async (_state: ContextState) => ({})

/**
 * Assemble retrieved instructions into a context string within the token budget.
 *
 * ARCH: Uses chars/4 approximation for token estimation. Instructions are included
 * in priority order (as returned by pgvector distance sort) until the budget is exhausted.
 */
export const assembleContext = async (state: ContextState) => {
  if (!state.instructions?.length) return { assembled_context: null, token_count: 0 }

  // CONSTRAINT: chars/4 is a rough approximation. Upgrade to tiktoken when accuracy matters.
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

/** Placeholder for response generation — context is returned to the caller as-is. */
export const generateResponse = async (_state: ContextState) => ({})

/**
 * Create the Phase 3 context assembly workflow.
 * Linear pipeline: policy → vector search → assemble → generate.
 */
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
