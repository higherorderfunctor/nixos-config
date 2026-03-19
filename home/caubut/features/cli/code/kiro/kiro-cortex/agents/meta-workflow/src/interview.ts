/**
 * @module meta-workflow/interview
 * Interview block — iterative HITL loop that gathers workflow requirements.
 *
 * ARCH: Loops until user confirms the design. Each iteration:
 * 1. Interrupt with question (includes accumulated context)
 * 2. User responds via orchestrating agent
 * 3. Parse response, accumulate in interview_messages, update state
 * 4. If user signals done → set interview_complete, present architecture summary
 * 5. If not done → graph routes back to interview (self-loop)
 *
 * ARCH: This is the sequential-thinking-with-RAG-reload pattern. Today the loop
 * accumulates context; future: each iteration re-queries RAG with evolving context
 * so instructions refine as the conversation deepens.
 *
 * ARCH: Adaptive behavior based on state context (UC-MW-34, 5.1 Q1).
 */

import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType, BlockSpec } from "./state.js"

interface InterviewAnswer {
  readonly workflow_name?: string
  readonly workflow_description?: string
  readonly blocks?: ReadonlyArray<BlockSpec>
  readonly needs_research?: boolean
  readonly trigger_type?: "agent" | "skill"
  readonly domain?: string
  readonly agent_role?: string
  /** User signals interview is complete — proceed to decompose. */
  readonly done?: boolean
}

function parseAnswer(raw: unknown): InterviewAnswer & { text: string } {
  if (typeof raw === "string") {
    try {
      const parsed = JSON.parse(raw) as InterviewAnswer & { description?: string }
      return { ...parsed, workflow_description: parsed.workflow_description ?? parsed.description, text: raw }
    } catch {
      return { text: raw }
    }
  }
  const obj = raw as InterviewAnswer & { description?: string }
  return { ...obj, workflow_description: obj.workflow_description ?? obj.description, text: JSON.stringify(raw) }
}

function buildQuestion(state: MetaWorkflowStateType): string {
  const history = state.interview_messages
  const isFirstTurn = history.length === 0

  const researchCtx = state.research_findings
    ? `\n\nResearch findings:\n${state.research_findings}`
    : ""

  const initialCtx = state.initial_prompt && isFirstTurn
    ? `\n\nInitial context from user:\n${state.initial_prompt}`
    : ""

  // Show accumulated state so orchestrator has full picture each iteration
  const accumulated = !isFirstTurn
    ? `\n\nAccumulated state so far:`
      + (state.workflow_name ? `\n- name: ${state.workflow_name}` : "")
      + (state.workflow_description ? `\n- description: ${state.workflow_description}` : "")
      + (state.domain ? `\n- domain: ${state.domain}` : "")
      + (state.agent_role ? `\n- agent_role: ${state.agent_role}` : "")
      + (state.trigger_type ? `\n- trigger_type: ${state.trigger_type}` : "")
      + (state.blocks?.length ? `\n- blocks: ${state.blocks.map(b => b.id).join(", ")}` : "")
      + `\n\nConversation history (${history.length} messages):\n${history.map((m, i) => `[${i + 1}] ${m}`).join("\n")}`
    : ""

  // Context detection (UC-MW-34)
  if (state.workflow_id && state.block_id) {
    return `Refining block "${state.block_id}" in workflow "${state.workflow_name}".${researchCtx}${accumulated}\n\nWhat needs to change?`
  }
  if (state.workflow_id) {
    return `Updating workflow "${state.workflow_name}".${researchCtx}${accumulated}\n\nWhat changes are needed?`
  }

  // Build mode
  if (isFirstTurn) {
    return `Interview loop started. Gather workflow requirements iteratively.\n\nNeeded: name, description, domain, agent_role, trigger_type (agent|skill), blocks.\n\nPresent each interrupt to the user. Resume with their answer as JSON or free text.\nWhen the user confirms the design, resume with { "done": true } to proceed to decompose.${researchCtx}${initialCtx}`
  }

  return `Interview continues.${researchCtx}${accumulated}\n\nContinue gathering requirements. When the user confirms the design, resume with { "done": true }.`
}

export function interviewNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  const question = buildQuestion(state)
  const raw: unknown = interrupt({ question })
  const answer = parseAnswer(raw)

  const fields = {
    workflow_name: answer.workflow_name ?? state.workflow_name,
    workflow_description: answer.workflow_description ?? state.workflow_description,
    blocks: answer.blocks ?? state.blocks,
    needs_research: answer.needs_research ?? false,
    trigger_type: answer.trigger_type ?? state.trigger_type,
    domain: answer.domain ?? state.domain,
    agent_role: answer.agent_role ?? state.agent_role,
    interview_messages: [answer.text],
    initial_prompt: "",
  }

  if (answer.done) {
    return { ...fields, interview_complete: true }
  }

  return { ...fields, interview_complete: false }
}
