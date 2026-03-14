/**
 * @module meta-workflow/promote
 * Promote block — generates trigger artifacts so workflows are discoverable.
 *
 * ARCH: Generates SKILL.md (kiro-cli skill trigger) and agent config JSON
 * (.kiro/agents/*.json) for workflow-specific agents. Uses interrupt() to
 * let the user choose which artifacts to generate (UC-MW-20).
 *
 * ARCH: Agent configs are specialized per workflow — not one generic worker.
 * Each config includes only the MCP tools the workflow needs (UC-MW-20).
 */

import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Generate a SKILL.md trigger file for kiro-cli discovery.
 *
 * ARCH: Skills are the entry point for users to invoke workflows.
 * The SKILL.md describes what the workflow does and how to trigger it.
 */
const generateSkillMd = (state: MetaWorkflowStateType): string => {
  const blockList = state.blocks
    .map((b) => `- **${b.name}**: ${b.description}`)
    .join("\n")

  return [
    `# ${state.workflow_name}`,
    "",
    state.workflow_description,
    "",
    "## Trigger",
    "",
    `- **Manual**: User invokes with \`/skill ${state.workflow_name}\``,
    "",
    "## Blocks",
    "",
    blockList,
    "",
    "## MCP Tools",
    "",
    `- \`run_workflow\` with workflow_id: "${state.workflow_name}"`,
    "",
  ].join("\n")
}

/**
 * Generate a Kiro agent config JSON for workflow-specific execution.
 *
 * ARCH: Specialized agents per workflow (UC-MW-20). The agent config
 * includes kiro-cortex MCP + OpenMemory MCP as minimum tool set.
 */
const generateAgentConfig = (state: MetaWorkflowStateType): string =>
  JSON.stringify(
    {
      name: `${state.workflow_name}-agent`,
      description: state.workflow_description,
      model: "auto",
      prompt: [
        `You are executing the "${state.workflow_name}" workflow.`,
        "",
        state.workflow_description,
        "",
        "Use kiro-cortex MCP tools to execute workflow blocks.",
        "Follow instructions provided by each block's OPA-scoped context.",
      ].join("\n"),
      allowedTools: [
        "openmemory_query",
        "openmemory_store",
        "sequentialthinking",
        "thinking",
      ],
      includeMcpJson: true,
    },
    null,
    2,
  )

/**
 * Present trigger artifact options and generate chosen artifacts.
 *
 * @returns Partial state with promoted_artifacts (file paths written).
 */
export const promoteNode = async (
  state: MetaWorkflowStateType,
): Promise<Partial<MetaWorkflowStateType>> => {
  const answer: unknown = interrupt({
    question: [
      `Generate trigger artifacts for "${state.workflow_name}"?`,
      "Options: skill (SKILL.md), agent (agent config JSON), both, skip",
    ].join("\n"),
    preview: {
      skill: `workflows/${state.workflow_name}/SKILL.md`,
      agent: `.kiro/agents/${state.workflow_name}-agent.json`,
    },
  })

  const choice = (typeof answer === "string" ? answer : "both").trim().toLowerCase()
  if (choice === "skip") return { promoted_artifacts: [] }

  const artifacts: Array<string> = []
  const wfDir = join(process.cwd(), "workflows", state.workflow_name)
  await mkdir(wfDir, { recursive: true })

  if (choice === "skill" || choice === "both") {
    const path = join(wfDir, "SKILL.md")
    await writeFile(path, generateSkillMd(state))
    artifacts.push(path)
  }

  if (choice === "agent" || choice === "both") {
    const dir = join(process.cwd(), ".kiro", "agents")
    await mkdir(dir, { recursive: true })
    const path = join(dir, `${state.workflow_name}-agent.json`)
    await writeFile(path, generateAgentConfig(state) + "\n")
    artifacts.push(path)
  }

  return { promoted_artifacts: artifacts }
}
