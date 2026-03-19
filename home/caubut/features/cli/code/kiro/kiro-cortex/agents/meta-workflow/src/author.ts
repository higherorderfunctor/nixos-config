/**
 * @module meta-workflow/author
 * Author block — generates instruction text for each block and writes YAML files.
 *
 * ARCH: For each block in the workflow spec, generates instruction text and exports
 * it as a YAML file to the filesystem. This is the "self-updating" capability
 * (UC-MW-17) — the meta-workflow writes its own instruction files.
 *
 * ARCH: Content hash (MD5 of instruction text) is included in YAML for change
 * detection during the startup YAML → pgvector loading process.
 */

import { createHash } from "node:crypto"
import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import type { MetaWorkflowStateType } from "./state.js"

/** Compute MD5 hash of instruction text for change detection. */
const contentHash = (text: string): string =>
  createHash("md5").update(text).digest("hex")

/**
 * Generate instruction text for each block and write YAML files to disk.
 *
 * @returns Partial state with instructions map (block_id → instruction text).
 */
export const authorNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const instructions: Record<string, string> = {}
  if (!state.blocks?.length) return { instructions }

  const dir = join(process.cwd(), "agents", state.workflow_name, "instructions")
  await mkdir(dir, { recursive: true })

  for (const block of state.blocks) {
    // ARCH: Simple template for now — will be enhanced when the meta-workflow
    // consumes its own OPA-scoped instructions for authoring guidance.
    const text = `You are executing the "${block.name}" block.\n\n${block.description}`
    instructions[block.id] = text

    // --- Write YAML instruction file for Nix reproducibility (UC-MW-16) ---
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
