/**
 * @module meta-workflow/optimize
 * Optimize block — checks workflow structure for bloat, spaghetti, and DRY violations.
 *
 * ARCH: Rule-based analysis (no LLM). Returns recommendations via interrupt()
 * so the user can decide whether to redesign. Sets needs_redesign flag to
 * loop back to decompose if the user wants changes.
 *
 * ARCH: Scope is LOCAL to the workflow being worked on during create/update.
 * Full repo-wide scan only via audit mode (UC-MW-13). Checks:
 * - Instruction bloat per block (UC-MW-8)
 * - Spaghetti detection — too many blocks (UC-MW-9)
 * - DRY violations — similar block descriptions (UC-MW-10)
 */

import { interrupt } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

/** Single optimization finding with severity. */
interface Finding {
  readonly severity: "warning" | "error"
  readonly rule: string
  readonly message: string
}

/** CONSTRAINT: Thresholds are intentionally conservative for MVP. */
const MAX_BLOCKS = 10
const SIMILARITY_THRESHOLD = 0.6

/**
 * Simple word-overlap similarity between two strings.
 * ARCH: Good enough for DRY detection — not a vector similarity.
 */
const wordSimilarity = (a: string, b: string): number => {
  const wa = new Set(a.toLowerCase().split(/\s+/))
  const wb = new Set(b.toLowerCase().split(/\s+/))
  const intersection = [...wa].filter((w) => wb.has(w)).length
  const union = new Set([...wa, ...wb]).size
  return union === 0 ? 0 : intersection / union
}

/**
 * Analyze workflow structure and report issues.
 *
 * If no issues: passes through silently (needs_redesign = false).
 * If issues found: interrupt() with findings, user decides to redesign or proceed.
 *
 * @returns Partial state with optimization_report and needs_redesign flag.
 */
export function optimizeNode(state: MetaWorkflowStateType): Partial<MetaWorkflowStateType> {
  const findings: Array<Finding> = []

  // --- UC-MW-9: Spaghetti detection ---
  if (state.blocks.length > MAX_BLOCKS) {
    findings.push({
      severity: "warning",
      rule: "spaghetti",
      message: `${state.blocks.length} blocks exceeds recommended max of ${MAX_BLOCKS}. Consider merging related blocks.`,
    })
  }

  // --- UC-MW-10: DRY violations (similar descriptions) ---
  for (let i = 0; i < state.blocks.length; i++) {
    for (let j = i + 1; j < state.blocks.length; j++) {
      const sim = wordSimilarity(state.blocks[i].description, state.blocks[j].description)
      if (sim > SIMILARITY_THRESHOLD) {
        findings.push({
          severity: "warning",
          rule: "dry-violation",
          message: `Blocks "${state.blocks[i].id}" and "${state.blocks[j].id}" have similar descriptions (${Math.round(sim * 100)}% overlap). Consider merging or abstracting a shared block.`,
        })
      }
    }
  }

  // --- UC-MW-8: Blocks with empty descriptions ---
  for (const block of state.blocks) {
    if (!block.description.trim()) {
      findings.push({
        severity: "error",
        rule: "missing-description",
        message: `Block "${block.id}" has no description. Descriptions are used for OPA instruction matching.`,
      })
    }
  }

  if (findings.length === 0) {
    return { optimization_report: "No issues found.", needs_redesign: false }
  }

  // ARCH: interrupt() presents findings. User responds with "proceed" or
  // provides revised block specs to trigger a redesign loop.
  const report = findings
    .map((f) => `[${f.severity.toUpperCase()}] ${f.rule}: ${f.message}`)
    .join("\n")

  const answer: unknown = interrupt({
    optimization_report: report,
    question: 'Review findings above. Reply "proceed" to continue, or provide revised blocks JSON to redesign.',
  })

  const redesign = typeof answer === "string" && answer.trim().toLowerCase() !== "proceed"
  return { optimization_report: report, needs_redesign: redesign }
}
