/**
 * @module meta-workflow/seed
 * Seed function — reads workflow YAML files from disk and returns data for DB insertion (UC-MW-16).
 *
 * ARCH: Inverse of export/author/wire. Reads the three YAML files per workflow:
 *   workflows/<name>/workflow.yaml       → metadata + block specs
 *   workflows/<name>/pipeline.yaml       → block ordering
 *   workflows/<name>/instructions/*.yaml → instruction text + OPA metadata
 *
 * ARCH: Does NOT embed text — caller is responsible for embedding and DB insertion.
 * This keeps seed pure (filesystem → data) with no DB/embedding dependencies.
 *
 * ARCH: Uses content_hash from instruction YAML for change detection. Caller can
 * compare hashes against DB to skip unchanged instructions (incremental load).
 */

import { readdir, readFile } from "node:fs/promises"
import { join } from "node:path"
import { parse } from "yaml"

/** A single instruction ready for embedding and DB insertion. */
export interface SeedInstruction {
  readonly block_id: string
  readonly text: string
  readonly content_hash: string
  readonly metadata: {
    readonly agent_role: string
    readonly task_type: string
    readonly domain: string
    readonly repo: string | null
  }
}

/** A complete workflow definition loaded from disk. */
export interface SeedWorkflow {
  readonly name: string
  readonly description: string
  readonly trigger_type: "agent" | "skill" | null
  readonly blocks: ReadonlyArray<{
    readonly id: string
    readonly name: string
    readonly description: string
    readonly execution_env?: "inline" | "subagent" | "ai-orchestrated"
  }>
  readonly pipeline_yaml: string
  readonly instructions: ReadonlyArray<SeedInstruction>
}

/**
 * Load a single workflow from its directory on disk.
 *
 * @param workflowDir Absolute path to workflows/<name>/
 * @returns Parsed workflow data ready for DB insertion.
 */
export const loadWorkflow = async (workflowDir: string): Promise<SeedWorkflow> => {
  // --- Read workflow metadata ---
  const workflowYaml = parse(await readFile(join(workflowDir, "workflow.yaml"), "utf-8")) as {
    name: string; description: string; trigger_type: string | null
    blocks: Array<{ id: string; name: string; description: string; execution_env?: string }>
  }

  // --- Read pipeline ---
  const pipelineYaml = await readFile(join(workflowDir, "pipeline.yaml"), "utf-8")

  // --- Read instructions (recursive walk, multi-instruction support) ---
  const instrDir = join(workflowDir, "instructions")
  const instructions: SeedInstruction[] = []

  const walkInstructions = async (dir: string): Promise<void> => {
    const entries = await readdir(dir, { withFileTypes: true }).catch(() => [])
    for (const entry of entries) {
      const full = join(dir, entry.name)
      if (entry.isDirectory()) { await walkInstructions(full); continue }
      if (!entry.name.endsWith(".yaml")) continue
      const raw = parse(await readFile(full, "utf-8"))
      const docs = raw && typeof raw === "object" && "instructions" in raw && Array.isArray(raw.instructions)
        ? raw.instructions
        : [raw]
      for (const parsed of docs) {
        instructions.push({
          block_id: parsed.id,
          text: parsed.text,
          content_hash: parsed.content_hash,
          metadata: parsed.metadata,
        })
      }
    }
  }
  await walkInstructions(instrDir)

  return {
    name: workflowYaml.name,
    description: workflowYaml.description,
    trigger_type: workflowYaml.trigger_type as "agent" | "skill" | null,
    blocks: workflowYaml.blocks.map((b) => {
      const block: {
        readonly id: string
        readonly name: string
        readonly description: string
        readonly execution_env?: "inline" | "subagent" | "ai-orchestrated"
      } = {
        id: b.id,
        name: b.name,
        description: b.description,
      }
      if (b.execution_env) {
        return { ...block, execution_env: b.execution_env as "inline" | "subagent" | "ai-orchestrated" }
      }
      return block
    }),
    pipeline_yaml: pipelineYaml,
    instructions,
  }
}

/**
 * Discover and load all workflows from the workflows/ directory.
 *
 * @param baseDir Absolute path to the workflows/ directory.
 * @returns Array of parsed workflows.
 */
export const loadAllWorkflows = async (baseDir: string): Promise<ReadonlyArray<SeedWorkflow>> => {
  const entries = await readdir(baseDir, { withFileTypes: true })
  const dirs = entries.filter((e) => e.isDirectory() && e.name !== "shared")
  const workflows: SeedWorkflow[] = []

  for (const dir of dirs) {
    const workflowDir = join(baseDir, dir.name)
    // Skip directories without workflow.yaml (e.g., incomplete exports)
    try {
      workflows.push(await loadWorkflow(workflowDir))
    } catch {
      // Skip malformed workflow directories silently
    }
  }

  return workflows
}
