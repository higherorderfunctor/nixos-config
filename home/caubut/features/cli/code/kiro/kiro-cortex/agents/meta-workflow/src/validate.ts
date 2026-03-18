/**
 * @module meta-workflow/validate
 * Validate block — pre-promote quality gate (UC-MW-35).
 *
 * ARCH: Tiered checks with confidence-based resolution (5.4 decisions):
 * - Tier 1 (structural, deterministic): filesystem artifacts, pipeline↔block, YAML schema
 * - Tier 2 (quality, LLM-assessed): instruction bloat, local DRY, scoped re-optimize — STUB
 * - Tier 3 (semantic, LLM-powered): arch doc coverage, cross-workflow DRY — STUB
 *
 * ARCH: Subsumes UC-MW-29 (structural lint), UC-MW-14 (scoped re-optimize),
 * UC-MW-13 (cross-workflow DRY), UC-MW-33 (semantic gap analysis).
 *
 * ARCH: Confidence drives escalation, not tier number (5.4 Q9).
 * Clean or confident fixes → promote. Low confidence → interview (UC-MW-36/37).
 */

import { type GapFinding, lintArtifactsNode } from "./lint-artifacts.js"
import type { MetaWorkflowStateType } from "./state.js"

/** Validate result with tier classification. */
interface ValidateResult {
  readonly tier: 1 | 2 | 3
  readonly findings: ReadonlyArray<GapFinding>
  readonly confident: boolean
}

/** Run tier 1 structural checks (delegates to lint-artifacts logic). */
const runTier1 = async (state: MetaWorkflowStateType): Promise<ValidateResult> => {
  const result = await lintArtifactsNode(state)
  const report = result.optimization_report ?? ""
  const hasErrors = report !== "No gaps found." && report.length > 0
  // Tier 1 is deterministic — always confident
  return {
    tier: 1,
    findings: hasErrors
      ? report.split("\n").map((line): GapFinding => ({
          severity: line.startsWith("[ERROR]") ? "error" : "warning",
          category: "filesystem",
          message: line,
        }))
      : [],
    confident: true,
  }
}

/** Tier 2 stub — quality checks (instruction bloat, local DRY, scoped re-optimize). */
const _runTier2 = async (_state: MetaWorkflowStateType): Promise<ValidateResult> =>
  ({ tier: 2, findings: [], confident: true })

/** Tier 3 stub — semantic checks (arch doc coverage, cross-workflow DRY). */
const _runTier3 = async (_state: MetaWorkflowStateType): Promise<ValidateResult> =>
  ({ tier: 3, findings: [], confident: true })

/**
 * Validate workflow artifacts before promote.
 *
 * ARCH: Runs all tiers, aggregates findings. If any tier has low confidence,
 * escalates to interview (interactive) or fails (programmatic, UC-MW-37).
 */
export const validateNode = async (
  state: MetaWorkflowStateType,
): Promise<Partial<MetaWorkflowStateType>> => {
  const results = await Promise.all([
    runTier1(state),
    _runTier2(state),
    _runTier3(state),
  ])

  const allFindings = results.flatMap((r) => r.findings)
  const allConfident = results.every((r) => r.confident)

  if (allFindings.length === 0) {
    return { validation_result: "All checks passed.", needs_interview: false }
  }

  const report = allFindings.map((f) => f.message).join("\n")

  // ARCH: Confidence-based escalation (5.4 Q9).
  // Low confidence on any tier → needs_interview for interactive, fail for programmatic.
  return {
    validation_result: report,
    needs_interview: !allConfident,
  }
}
