/**
 * @module meta-workflow/promote
 * Promote block — generates trigger artifacts so workflows are discoverable.
 *
 * ARCH: Based on UC-MW-26 trigger_type from interview:
 * - "skill" → generates SKILL.md (+ optional references/) in .kiro/skills/ or ~/.kiro/skills/
 * - "agent" → generates comprehensive agent config JSON in .kiro/agents/ or ~/.kiro/agents/
 * - null/both → interrupt to ask, then generate chosen artifact
 *
 * ARCH: Agent configs follow kiro.dev/docs/cli/custom-agents/configuration-reference.
 * Skills follow the Agent Skills standard (agentskills.io).
 */

import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

// ---------------------------------------------------------------------------
// SKILL.md generation
// ---------------------------------------------------------------------------

const generateSkillMd = (state: MetaWorkflowStateType): string => {
  const blockList = state.blocks
    .map((b) => `- **${b.name}**: ${b.description}`)
    .join("\n")

  return [
    "---",
    `name: ${state.workflow_name}`,
    `description: ${state.workflow_description}`,
    "---",
    "",
    `# ${state.workflow_name}`,
    "",
    state.workflow_description,
    "",
    "## Trigger",
    "",
    "- **Automatic**: Activated when request matches description above",
    "",
    "## Workflow",
    "",
    blockList,
    "",
    "## MCP Tools",
    "",
    `- \`run_workflow\` with workflow_id: "${state.workflow_name}"`,
    "",
  ].join("\n")
}

// ---------------------------------------------------------------------------
// Agent config generation
// ---------------------------------------------------------------------------

const generateAgentPrompt = (state: MetaWorkflowStateType): string => [
  `You are executing the "${state.workflow_name}" workflow.`,
  "",
  state.workflow_description,
  "",
  "## Workflow Execution",
  "",
  "Use kiro-cortex MCP tools to execute workflow blocks.",
  "Follow instructions provided by each block's OPA-scoped context.",
  "",
  "When run_workflow returns a BlockOutput:",
  '- If next_step.type is "resume": call run_workflow with the same thread_id',
  '- If next_step.type is "spawn_subagent": call use_subagent with the specified agent and task',
  '- If next_step.type is "ask_user": present the question to the user, then resume with their answer',
  '- If next_step.type is "complete": present the summary — workflow is done',
  "",
  "## Subagent Constraints",
  "",
  "Subagents cannot use: web_search, web_fetch, introspect, thinking, todo_list, use_aws, grep, glob.",
  "Blocks requiring these must run in parent conversation or deterministic pipeline.",
].join("\n")

const generateAgentConfig = (state: MetaWorkflowStateType): string =>
  JSON.stringify(
    {
      name: `${state.workflow_name}-agent`,
      description: state.workflow_description,
      model: "auto",
      prompt: generateAgentPrompt(state),
      tools: ["*"],
      allowedTools: [
        "@openmemory",
        "@sequentialthinking",
        "fs_read",
        "code",
      ],
      includeMcpJson: true,
      resources: [
        "skill://.kiro/skills/**/SKILL.md",
        "skill://~/.kiro/skills/**/SKILL.md",
        "file://.kiro/steering/**/*.md",
      ],
      hooks: {
        agentSpawn: [{ command: "git status" }],
      },
    },
    null,
    2,
  )

// ---------------------------------------------------------------------------
// Promote node
// ---------------------------------------------------------------------------

export const promoteNode = async (
  state: MetaWorkflowStateType,
): Promise<Partial<MetaWorkflowStateType>> => {
  // Determine trigger type — use interview answer or ask now
  let choice = state.trigger_type
  if (!choice) {
    const answer: unknown = interrupt({
      question: [
        `Generate trigger artifact for "${state.workflow_name}"?`,
        "- skill: SKILL.md (default agent activates on request match)",
        "- agent: dedicated agent config (user switches explicitly)",
        "- skip: no artifact",
      ].join("\n"),
    })
    const raw = (typeof answer === "string" ? answer : "skill").trim().toLowerCase()
    if (raw === "skip") return { promoted_artifacts: [] }
    choice = raw === "agent" ? "agent" : "skill"
  }

  const artifacts: Array<string> = []

  if (choice === "skill") {
    const dir = join(process.cwd(), ".kiro", "skills", state.workflow_name)
    await mkdir(dir, { recursive: true })
    const path = join(dir, "SKILL.md")
    await writeFile(path, generateSkillMd(state))
    artifacts.push(path)
  } else {
    const dir = join(process.cwd(), ".kiro", "agents")
    await mkdir(dir, { recursive: true })
    const path = join(dir, `${state.workflow_name}-agent.json`)
    await writeFile(path, generateAgentConfig(state) + "\n")
    artifacts.push(path)
  }

  return { promoted_artifacts: artifacts }
}
