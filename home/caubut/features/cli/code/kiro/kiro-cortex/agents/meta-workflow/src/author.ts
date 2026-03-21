/**
 * @module meta-workflow/author
 * Author block — uses HITL interrupt to generate substantive instruction text
 * for each block, then writes YAML files to disk.
 *
 * ARCH: Interrupts with full workflow context (interview history, block specs,
 * research findings) so the orchestrating agent can write real operational
 * instructions — not just block descriptions. Each block gets instructions
 * that tell an LLM exactly how to execute it.
 *
 * ARCH: Content hash (MD5 of instruction text) is included in YAML for change
 * detection during the startup YAML → pgvector loading process.
 */

import { createHash } from "node:crypto"
import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

const contentHash = (text: string): string =>
  createHash("md5").update(text).digest("hex")

export const authorNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const instructions: Record<string, string> = {}
  if (!state.blocks?.length) return { instructions }

  // Interrupt with full context so orchestrator writes real instructions
  const context = {
    task: "author_instructions",
    workflow_name: state.workflow_name,
    workflow_description: state.workflow_description,
    domain: state.domain,
    agent_role: state.agent_role,
    blocks: state.blocks,
    research_findings: state.research_findings || "(none)",
    interview_history: state.interview_messages,
    instructions: [
      "Write substantive instruction text for EACH block listed above.",
      "Each instruction must tell an LLM exactly how to execute that block:",
      "  - What inputs to read from state",
      "  - What logic to perform (decision trees, validations, transformations)",
      "  - What outputs to write back to state",
      "  - Edge cases and error handling",
      "  - How this block connects to adjacent blocks in the pipeline",
      "",
      "Return a JSON object mapping block_id → instruction_text string.",
      'Example: { "navigate": "You are the navigate block...\\n\\n## Inputs\\n...", ... }',
      "",
      "Do NOT return trivial one-liners. Each instruction should be 10-30 lines",
      "of operational guidance that an LLM can follow without additional context.",
    ].join("\n"),
  }

  const answer: unknown = interrupt(context)

  // Parse: expect Record<string, string> mapping block_id → instruction text
  const authored: Record<string, string> = typeof answer === "string"
    ? JSON.parse(answer) as Record<string, string>
    : answer as Record<string, string>

  const dir = join(process.cwd(), "agents", state.workflow_name, "instructions")
  await mkdir(dir, { recursive: true })

  for (const block of state.blocks) {
    const text = authored[block.id] ?? `You are executing the "${block.name}" block.\n\n${block.description}`
    instructions[block.id] = text

    const yaml = [
      `id: "${block.id}"`,
      "text: |",
      ...text.split("\n").map((l) => `  ${l}`),
      "metadata:",
      `  agent_role: "${state.agent_role || "workflow-builder"}"`,
      `  task_type: "${block.id}"`,
      `  domain: "${state.domain || "meta"}"`,
      "  repo: null",
      `content_hash: "${contentHash(text)}"`,
    ].join("\n")
    await writeFile(join(dir, `${block.id}.yaml`), yaml + "\n")
  }

  return { instructions }
}
