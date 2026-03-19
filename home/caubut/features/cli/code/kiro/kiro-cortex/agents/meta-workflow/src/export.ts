/**
 * @module meta-workflow/export
 * Export block — writes workflow metadata YAML for Nix reproducibility (UC-MW-16).
 *
 * ARCH: Complements author.ts (instruction YAML) and wire.ts (pipeline YAML).
 * This writes the top-level workflow.yaml with metadata that can't be derived
 * from instructions alone: trigger_type, block specs with execution_env.
 *
 * ARCH: Together, these three files make a workflow fully reconstructable:
 *   agents/<name>/
 *   ├── workflow.yaml       # metadata (this file)
 *   ├── pipeline.yaml       # block ordering (wire.ts)
 *   ├── instructions/       # instruction text per block (author.ts)
 *   │   └── <block-id>.yaml
 *   ├── src/                # block implementations (manual)
 *   └── docs/               # architecture, design docs
 */

import { mkdir, writeFile } from "node:fs/promises"
import { join } from "node:path"
import { Effect, Layer } from "effect"
import { loadInstructions, instructionLayer, embeddingLayer, SqlLive } from "kiro-cortex"
import type { MetaWorkflowStateType } from "./state.js"

/**
 * Export workflow metadata to YAML for filesystem persistence.
 *
 * @returns Unchanged state (export is a side effect).
 */
export const exportNode = async (state: MetaWorkflowStateType): Promise<Partial<MetaWorkflowStateType>> => {
  const dir = join(process.cwd(), "agents", state.workflow_name)
  await mkdir(join(dir, "src"), { recursive: true })
  await mkdir(join(dir, "docs"), { recursive: true })
  await mkdir(join(dir, "instructions"), { recursive: true })

  const blocksYaml = state.blocks.map((b) => [
    `  - id: "${b.id}"`,
    `    name: "${b.name}"`,
    `    description: "${b.description}"`,
    b.execution_env ? `    execution_env: "${b.execution_env}"` : null,
  ].filter(Boolean).join("\n")).join("\n")

  const yaml = [
    `name: "${state.workflow_name}"`,
    `description: "${state.workflow_description}"`,
    `trigger_type: ${state.trigger_type ? `"${state.trigger_type}"` : "null"}`,
    "blocks:",
    blocksYaml,
  ].join("\n")

  await writeFile(join(dir, "workflow.yaml"), yaml + "\n")

  // ARCH: Reload all instruction YAMLs into pgvector so newly authored
  // instructions are available for RAG immediately (not just on disk).
  await Effect.runPromise(
    loadInstructions.pipe(
      Effect.provide(Layer.mergeAll(instructionLayer, embeddingLayer).pipe(Layer.provide(SqlLive))),
    ),
  )

  return {}
}
