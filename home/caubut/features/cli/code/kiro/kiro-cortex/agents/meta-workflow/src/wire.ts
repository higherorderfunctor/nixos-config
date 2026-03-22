/**
 * @module meta-workflow/wire
 * Wire block — generates pipeline YAML definition from the workflow spec.
 *
 * ARCH: Creates the pipeline.yaml file that defines block ordering and routing.
 * This file is read by the YAML loader at startup to register the pipeline.
 * Together with author (instruction YAML), this makes workflows fully
 * reconstructable from files on disk (Nix reproducibility, UC-MW-16).
 */

import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Generate pipeline.yaml from the workflow spec and write to disk.
 *
 * @returns Partial state with the generated pipeline YAML string.
 */
export const wireNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const dir = join(process.cwd(), "agents", state.workflow_name)
  await mkdir(dir, { recursive: true })

  // --- Generate pipeline YAML with linear step ordering ---
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
