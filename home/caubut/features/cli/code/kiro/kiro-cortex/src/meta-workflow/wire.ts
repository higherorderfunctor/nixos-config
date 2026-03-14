import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import type { MetaWorkflowStateType } from "./state.js"

export const wireNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const dir = join(process.cwd(), "workflows", state.workflow_name)
  await mkdir(dir, { recursive: true })

  const steps = state.blocks.map((b) => `  - block_id: "${b.id}"`).join("\n")
  const yaml = [
    `id: "${state.workflow_name}"`,
    `name: "${state.workflow_name}"`,
    `description: "${state.workflow_description}"`,
    "steps:",
    steps,
  ].join("\n")

  await writeFile(join(dir, "pipeline.yaml"), yaml + "\n")
  return { pipeline_yaml: yaml }
}
