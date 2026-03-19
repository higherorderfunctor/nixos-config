/**
 * Verify the test-script-pattern convention: import graph directly, invoke without MCP.
 * Requires: PG running on localhost:5435 (always-on systemd service).
 * Run: bun agents/meta-workflow/scripts/test-graph-direct.ts
 */
import { buildMetaWorkflow } from "../src/graph.js"
import { Command, isInterrupted, INTERRUPT } from "@langchain/langgraph"

const graph = await buildMetaWorkflow()
const tid = `test-direct-${Date.now()}`
const config = { configurable: { thread_id: tid } }

// 1. Initial invoke — should hit interview interrupt
const r1 = await graph.invoke({ initial_prompt: "Test workflow" }, config)
const i1 = isInterrupted(r1)
  ? (r1 as Record<symbol, Array<{ value?: unknown }>>)[INTERRUPT].map((i) => i.value)
  : []
console.log("1. interrupted:", i1.length > 0, "— interrupts:", i1.length)

// 2. Resume with interview answers — should hit next interrupt or advance
const r2 = await graph.invoke(
  new Command({
    resume: {
      workflow_name: "test-wf",
      description: "Test",
      domain: "test",
      agent_role: "tester",
      trigger_type: "skill",
    },
  }),
  config,
)
const i2 = isInterrupted(r2)
  ? (r2 as Record<symbol, Array<{ value?: unknown }>>)[INTERRUPT].map((i) => i.value)
  : []
console.log("2. interrupted:", i2.length > 0, "— interview_complete:", r2.interview_complete)

console.log("\n✅ Direct graph invoke works — no MCP needed")
process.exit(0)
