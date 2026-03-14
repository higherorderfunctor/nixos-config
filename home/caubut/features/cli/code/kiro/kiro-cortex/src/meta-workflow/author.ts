import { createHash } from "node:crypto"
import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import type { MetaWorkflowStateType } from "./state.js"

const contentHash = (text: string): string =>
  createHash("md5").update(text).digest("hex")

export const authorNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const instructions: Record<string, string> = {}
  const dir = join(process.cwd(), "workflows", state.workflow_name, "instructions")
  await mkdir(dir, { recursive: true })

  for (const block of state.blocks) {
    const text = `You are executing the "${block.name}" block.\n\n${block.description}`
    instructions[block.id] = text
    const yaml = [
      `id: "${block.id}"`,
      "text: |",
      ...text.split("\n").map((l) => `  ${l}`),
      "metadata:",
      '  agent_role: "workflow-builder"',
      `  task_type: "${block.id}"`,
      '  domain: "meta"',
      "  repo: null",
      `content_hash: "${contentHash(text)}"`,
    ].join("\n")
    await writeFile(join(dir, `${block.id}.yaml`), yaml + "\n")
  }

  return { instructions }
}
