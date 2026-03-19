/**
 * @module meta-workflow/interview
 * Interview block — gathers workflow requirements from the user via HITL interrupt.
 *
 * ARCH: Adaptive behavior based on state context (UC-MW-34, 5.1 Q1):
 * - No workflow → "What do you want to build?"
 * - workflow_id → "What do you want to change?"
 * - workflow_id + block_id → narrows to that block
 * - (future: validate_findings → "Here are discrepancies, how should we resolve?")
 *
 * ARCH: Uses LangGraph interrupt() for human-in-the-loop. Sets needs_research
 * flag when the user indicates knowledge gaps. The graph routes
 * interview → research → interview when research is needed.
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
  /** How the workflow will be triggered (UC-MW-26). */
  readonly trigger_type?: "agent" | "skill"
  /** OPA domain for instruction scoping (e.g., "dungeon", "repo-analysis"). */
  readonly domain?: string
  /** OPA agent role for instruction scoping (e.g., "dungeon-runner"). */
  readonly agent_role?: string
}

/**
 * Interview the user about the workflow they want to build or update.
 * Pauses execution via interrupt() and waits for user input.
 *
 * ARCH: If initial_prompt is set (first turn), includes it as context in the
 * interrupt question. The orchestrating agent sees the user's intent and
 * interviews to solidify the design. Clears initial_prompt after consumption.
 *
 * ARCH: Adapts question based on state context (UC-MW-34):
 * - workflow_id + block_id → refine specific block
 * - workflow_id → update existing workflow
 * - neither → build new workflow
 *
 * @returns Partial state with workflow metadata and needs_research flag.
 */
export function interviewNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  const researchContext = state.research_findings
    ? `\n\nResearch findings from previous step:\n${state.research_findings}`
    : ""

  const triggerPrompt = "\n\nHow should this workflow be triggered?\n- agent: dedicated agent (user switches explicitly, focused context)\n- skill: default agent activates on request match (on-demand, lower context cost)"

  // ARCH: If initial_prompt is set, include it as context so the interviewer
  // sees the user's intent but still interrupts to ask clarifying questions.
  const initialContext = state.initial_prompt
    ? `\n\nInitial context from user:\n${state.initial_prompt}\n\nReview this context and interview the user to solidify the design.`
    : ""

  // ARCH: Context detection determines question framing (5.1 Q4, UC-MW-34)
  const question = state.workflow_id && state.block_id
    ? `Refining block "${state.block_id}" in workflow "${state.workflow_name}".${researchContext}\n\nWhat needs to change in this block's instructions?`
    : state.workflow_id
      ? `Updating workflow "${state.workflow_name}". What changes?${researchContext}\n\nProvide updated details. Set needs_research: true if you need external research first.`
      : `Describe the workflow: name, description, and optionally blocks.${researchContext}${triggerPrompt}\n\nSet needs_research: true if you want external research before decomposition.${initialContext}`

  // ARCH: Always interrupt — initial_prompt is context for the interviewer, not the answer.
  const answer: unknown = interrupt({ question })

  // CONSTRAINT: Answer can be a JSON string or pre-parsed object depending on caller
  const parsed: InterviewAnswer = typeof answer === "string"
    ? (() => { try { return JSON.parse(answer) as InterviewAnswer } catch { return { workflow_description: answer } as InterviewAnswer } })()
    : answer as InterviewAnswer

  return {
    workflow_name: parsed.workflow_name ?? state.workflow_name,
    workflow_description: parsed.workflow_description ?? state.workflow_description,
    blocks: parsed.blocks ?? state.blocks,
    needs_research: parsed.needs_research ?? false,
    trigger_type: parsed.trigger_type ?? state.trigger_type,
    domain: parsed.domain ?? state.domain,
    agent_role: parsed.agent_role ?? state.agent_role,
    initial_prompt: "", // consumed — future interview calls (e.g. from validate) will interrupt
  }
}
