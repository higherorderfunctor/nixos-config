// ARCH: Single Effect program — forks the HTTP backend, waits for it to be
// ready, then connects the MCP stdio transport. All logging suppressed so
// stdout stays clean for JSON-RPC.
import { main } from "./main.js"
import { Effect, Logger, LogLevel, Schedule } from "effect"
import * as BunPlatform from "@effect/platform-bun"
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js"
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js"
import { z } from "zod"

const CORTEX_URL = "http://localhost:3100"

const waitForBackend = Effect.tryPromise(() =>
  fetch(`${CORTEX_URL}/health`).then((r) => { if (!r.ok) throw r }),
).pipe(
  Effect.retry({ times: 50, schedule: Schedule.spaced("200 millis") }),
  Effect.asVoid,
)

const startMcp = Effect.async<never>(() => {
  const server = new McpServer({ name: "kiro-cortex", version: "0.1.0" })

  server.registerTool(
    "list_workflows",
    { description: "List available kiro-cortex workflows", inputSchema: z.object({}) },
    async () => {
      const res = await fetch(`${CORTEX_URL}/workflows`)
      const data: unknown = await res.json()
      return { content: [{ type: "text" as const, text: JSON.stringify(data, null, 2) }] }
    },
  )

  server.registerTool(
    "run_workflow",
    {
      description: "Run a kiro-cortex workflow by ID",
      inputSchema: z.object({
        id: z.string().describe("Workflow ID"),
        input: z.record(z.string(), z.unknown()).describe("Workflow input state").optional(),
        thread_id: z.string().describe("Thread ID for HITL resume").optional(),
      }),
    },
    async (params) => {
      const res = await fetch(`${CORTEX_URL}/workflows/${params.id}/invoke`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ input: params.input ?? {}, thread_id: params.thread_id }),
      })
      const data: unknown = await res.json()
      return { content: [{ type: "text" as const, text: JSON.stringify(data, null, 2) }] }
    },
  )

  server.registerTool(
    "reload_workflows",
    {
      description: "Reload workflow instructions from YAML files into the database. Use after editing workflow YAML files on disk.",
      inputSchema: z.object({}),
    },
    async () => {
      const res = await fetch(`${CORTEX_URL}/workflows/reload`, { method: "POST" })
      const data: unknown = await res.json()
      return { content: [{ type: "text" as const, text: JSON.stringify(data, null, 2) }] }
    },
  )

  const transport = new StdioServerTransport()
  server.connect(transport).then(() => console.error("kiro-cortex MCP server running on stdio"))
  // Never resume — MCP server runs until stdin closes
})

const program = Effect.gen(function* () {
  yield* main.pipe(Effect.fork)
  yield* waitForBackend
  yield* startMcp
})

BunPlatform.BunRuntime.runMain(
  program.pipe(Logger.withMinimumLogLevel(LogLevel.None)),
)
