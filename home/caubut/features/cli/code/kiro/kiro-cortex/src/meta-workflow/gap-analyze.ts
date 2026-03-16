/**
 * @module meta-workflow/gap-analyze
 * Gap analysis block — checks cross-system completeness for a workflow (UC-MW-29).
 *
 * ARCH: Broader than optimize (which checks instruction quality). Gap-analyze checks:
 * - Filesystem artifacts: workflow.yaml, pipeline.yaml, instruction YAMLs
 * - Pipeline ↔ instruction file consistency
 * - Block coverage (expected blocks vs actual files on disk)
 *
 * Runs deterministically — no interrupt. Findings flow into state for downstream
 * blocks (optimize adds its own, interview presents everything to user).
 */

import { access, readFile } from "node:fs/promises"
import { join } from "node:path"
import { parse } from "yaml"
import type { MetaWorkflowStateType } from "./state.js"

/** Single gap finding with severity and category. */
export interface GapFinding {
  readonly severity: "error" | "warning"
  readonly category: "filesystem" | "pipeline" | "instructions"
  readonly message: string
}

/** Check if a file exists. */
const exists = (path: string): Promise<boolean> =>
  access(path).then(() => true, () => false)

/**
 * Analyze a workflow for cross-system gaps.
 *
 * ARCH: Uses Node.js fs directly (same pattern as export.ts, author.ts).
 * Deterministic — no interrupt. Produces gap_analysis_report for downstream consumption.
 */
export const gapAnalyzeNode = async (
  state: MetaWorkflowStateType,
): Promise<Partial<MetaWorkflowStateType>> => {
  const findings: Array<GapFinding> = []
  const name = state.workflow_name
  const dir = join(process.cwd(), "workflows", name)

  // --- Filesystem artifact checks ---
  if (!(await exists(dir))) {
    findings.push({ severity: "error", category: "filesystem", message: `Workflow directory missing: workflows/${name}/` })
    return { gap_analysis_report: formatFindings(findings) }
  }

  const workflowYaml = join(dir, "workflow.yaml")
  const pipelineYaml = join(dir, "pipeline.yaml")
  const instrDir = join(dir, "instructions")

  if (!(await exists(workflowYaml)))
    findings.push({ severity: "error", category: "filesystem", message: "workflow.yaml missing" })
  if (!(await exists(pipelineYaml)))
    findings.push({ severity: "error", category: "filesystem", message: "pipeline.yaml missing" })
  if (!(await exists(instrDir)))
    findings.push({ severity: "error", category: "filesystem", message: "instructions/ directory missing" })

  // --- Pipeline ↔ instruction file consistency ---
  if (await exists(pipelineYaml)) {
    const raw = await readFile(pipelineYaml, "utf-8")
    const pipeline = parse(raw) as { steps?: Array<{ block_id: string }> }
    const pipelineBlockIds = (pipeline.steps ?? []).map((s) => s.block_id)

    // Check each pipeline step has a corresponding instruction YAML
    for (const blockId of pipelineBlockIds) {
      if (!(await exists(join(instrDir, `${blockId}.yaml`))))
        findings.push({ severity: "error", category: "instructions", message: `Instruction YAML missing for pipeline block "${blockId}"` })
    }

    // Check graph blocks vs pipeline steps (if blocks are in state)
    if (state.blocks.length > 0) {
      const stateBlockIds = new Set(state.blocks.map((b) => b.id))
      for (const pid of pipelineBlockIds) {
        if (!stateBlockIds.has(pid))
          findings.push({ severity: "warning", category: "pipeline", message: `Pipeline step "${pid}" not in block specs` })
      }
      for (const sid of stateBlockIds) {
        if (!pipelineBlockIds.includes(sid))
          findings.push({ severity: "warning", category: "pipeline", message: `Block "${sid}" not in pipeline.yaml` })
      }
    }
  }

  return { gap_analysis_report: formatFindings(findings) }
}

const formatFindings = (findings: Array<GapFinding>): string =>
  findings.length === 0
    ? "No gaps found."
    : findings.map((f) => `[${f.severity.toUpperCase()}] ${f.category}: ${f.message}`).join("\n")
