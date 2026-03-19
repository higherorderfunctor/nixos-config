/**
 * End-to-end test: simulate the full dungeon-crawler build flow.
 * Exercises every block, every interrupt, every resume — finds bugs before real run.
 *
 * Run: bun agents/meta-workflow/scripts/test-e2e-dungeon.ts
 */
import { buildMetaWorkflow } from "../src/graph.js"
import { Command, isInterrupted, INTERRUPT } from "@langchain/langgraph"
import { rm } from "node:fs/promises"
import { join } from "node:path"

const graph = await buildMetaWorkflow()
const tid = `test-e2e-${Date.now()}`
const config = { configurable: { thread_id: tid } }
let step = 0

function getInterrupts(result: Record<string, unknown>): unknown[] {
  return isInterrupted(result)
    ? (result as Record<symbol, Array<{ value?: unknown }>>)[INTERRUPT].map((i) => i.value)
    : []
}

async function invoke(input: unknown, label: string): Promise<Record<string, unknown>> {
  step++
  try {
    const result = await graph.invoke(input, config) as Record<string, unknown>
    const interrupts = getInterrupts(result)
    const stateKeys = Object.keys(result).filter(k => result[k] != null && result[k] !== "" && result[k] !== false)
    console.log(`${step}. [${label}] interrupted=${interrupts.length > 0} interrupts=${interrupts.length} state=[${stateKeys.join(",")}]`)
    if (interrupts.length > 0) {
      const val = interrupts[0]
      const preview = typeof val === "object" && val !== null
        ? JSON.stringify(val).slice(0, 200)
        : String(val).slice(0, 200)
      console.log(`   interrupt: ${preview}`)
    }
    return result
  } catch (e) {
    console.error(`${step}. [${label}] ❌ ERROR: ${e instanceof Error ? e.message : String(e)}`)
    throw e
  }
}

// Clean up any previous test artifacts
const artifactDir = join(process.cwd(), "agents", "dungeon-crawler-test-harness")
await rm(artifactDir, { recursive: true, force: true })

console.log("=== E2E Test: Dungeon Crawler Build via Meta-Workflow ===\n")

// --- Step 1: Initial invoke → should hit interview interrupt ---
const r1 = await invoke(
  { initial_prompt: "Build dungeon-crawler-test-harness. Domain: dungeon. Agent role: dungeon-runner. Trigger: agent." },
  "initial → route → interview",
)

// --- Step 2: Resume with interview answers ---
const r2 = await invoke(
  new Command({
    resume: {
      workflow_name: "dungeon-crawler-test-harness",
      workflow_description: "Procedural Myst-style dungeon crawler validating OPA→RAG→LangGraph at scale (100K+ facts)",
      domain: "dungeon",
      agent_role: "dungeon-runner",
      trigger_type: "agent",
    },
  }),
  "interview answers",
)

// --- Step 3: Resume with done → should advance to decompose ---
const r3 = await invoke(
  new Command({ resume: { done: true } }),
  "interview done → decompose",
)

// Check: did we get a decompose interrupt?
const i3 = getInterrupts(r3 as Record<string, unknown>)
if (i3.length === 0) {
  console.error("   ⚠️  Expected decompose interrupt but got none!")
  console.log("   interview_complete:", (r3 as any).interview_complete)
  console.log("   blocks:", (r3 as any).blocks)
}

// --- Step 4: Resume decompose with block specs ---
const blockSpecs = [
  { id: "navigate", name: "NAVIGATE", description: "Move player to adjacent room. Validates door exists and is unlocked. Retrieves tier 1 facts via OPA-scoped RAG.", execution_env: "inline" },
  { id: "assess", name: "ASSESS", description: "AI decision block. Analyzes current facts, inventory, visited rooms to decide next action.", execution_env: "subagent" },
  { id: "inspect", name: "INSPECT", description: "Examine a specific object in the current room. Retrieves tier 2 facts via OPA-scoped RAG.", execution_env: "inline" },
  { id: "pickup", name: "PICKUP", description: "Take an item from the current room into inventory. Validates item exists and is takeable.", execution_env: "inline" },
  { id: "combine", name: "COMBINE", description: "Merge two inventory items into a new item. Validates combination is valid per dungeon rules.", execution_env: "inline" },
  { id: "use_item", name: "USE_ITEM", description: "Apply an inventory item to a room object. Retrieves tier 3 facts via OPA-scoped RAG.", execution_env: "inline" },
  { id: "verify", name: "VERIFY", description: "Terminal block. Compares AI action sequence against deterministic solver optimal path.", execution_env: "inline" },
]

const r4 = await invoke(
  new Command({ resume: blockSpecs }),
  "decompose → blocks",
)

// --- Step 5: Optimize should either pass through or interrupt ---
const i4 = getInterrupts(r4 as Record<string, unknown>)
if (i4.length > 0) {
  // Optimize interrupted — respond with "proceed"
  const r5 = await invoke(
    new Command({ resume: "proceed" }),
    "optimize → proceed",
  )
  // After optimize, author runs (no interrupt), then wire (no interrupt),
  // then validate, then promote or more interrupts
} else {
  console.log("   optimize passed through (no findings)")
}

// --- Continue resuming until we hit END or error ---
// At this point we may be at: author (no interrupt) → wire (no interrupt) → validate → promote
// Let's keep going
let current = r4
let maxIterations = 10

while (maxIterations-- > 0) {
  const interrupts = getInterrupts(current as Record<string, unknown>)
  if (interrupts.length === 0) {
    // No interrupt — either we're done or something went wrong
    console.log(`\n=== Flow completed (no more interrupts) ===`)
    console.log("Final state keys:", Object.keys(current).filter(k => (current as any)[k] != null))
    console.log("workflow_name:", (current as any).workflow_name)
    console.log("blocks:", (current as any).blocks?.length)
    console.log("instructions:", Object.keys((current as any).instructions || {}))
    console.log("pipeline_yaml:", (current as any).pipeline_yaml ? "present" : "missing")
    console.log("validation_result:", (current as any).validation_result)
    console.log("promoted_artifacts:", (current as any).promoted_artifacts)
    console.log("error:", (current as any).error)
    break
  }

  // Determine what block is asking
  const interruptVal = interrupts[0] as Record<string, unknown>

  if (interruptVal?.optimization_report) {
    // Optimize interrupt
    current = await invoke(new Command({ resume: "proceed" }), "optimize → proceed") as Record<string, unknown>
  } else if (interruptVal?.question && String(interruptVal.question).includes("trigger artifact")) {
    // Promote interrupt (asking about trigger type)
    current = await invoke(new Command({ resume: "agent" }), "promote → agent") as Record<string, unknown>
  } else if (interruptVal?.question && String(interruptVal.question).includes("Research needed")) {
    // Research interrupt
    current = await invoke(new Command({ resume: "No research needed." }), "research → skip") as Record<string, unknown>
  } else if (interruptVal?.question && String(interruptVal.question).includes("Interview")) {
    // Interview callback from validate
    current = await invoke(new Command({ resume: { done: true } }), "validate→interview → done") as Record<string, unknown>
  } else {
    console.log(`   ⚠️  Unknown interrupt, attempting generic resume:`, JSON.stringify(interruptVal).slice(0, 300))
    current = await invoke(new Command({ resume: "proceed" }), "generic resume") as Record<string, unknown>
  }
}

if (maxIterations <= 0) {
  console.error("\n❌ Hit max iterations — possible infinite loop!")
}

// --- Cleanup ---
console.log("\n--- Cleanup ---")
// Clean test checkpoint
const { execSync } = await import("node:child_process")
try {
  execSync(`psql -h localhost -p 5435 -d kiro_cortex -c "DELETE FROM checkpoints WHERE thread_id = '${tid}';"`, { stdio: "pipe" })
  console.log("Cleaned PG checkpoint")
} catch { console.log("PG cleanup skipped") }

// Clean test artifacts
await rm(artifactDir, { recursive: true, force: true })
console.log("Cleaned artifact directory")

console.log("\n✅ E2E test complete")
