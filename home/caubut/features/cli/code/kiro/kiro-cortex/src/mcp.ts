// ARCH: Single Effect program — connects MCP stdio transport FIRST (so kiro-cli
// gets its initialize response immediately), then forks the HTTP backend. Tool
// handlers wait for the backend on demand. Set CORTEX_DEBUG=true to write logs
// to /tmp.
import { main } from "./main.js"
import { Config, Effect, Layer, Logger, LogLevel, Schedule } from "effect"
import * as BunPlatform from "@effect/platform-bun"
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js"
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js"
import { z } from "zod"
import { appendFileSync, writeFileSync } from "node:fs"

const CORTEX_URL = "http://localhost:3100"
const LOG_PATH = "/tmp/kiro-cortex-mcp.log"

const fileLogger = Logger.make(({ message, date, logLevel }) => {
  appendFileSync(LOG_PATH, `${date.toISOString()} [${logLevel.label}] ${String(message)}\n`)
})

const debug = process.env.CORTEX_DEBUG === "true" || process.env.CORTEX_DEBUG === "1"

const DebugLoggerLive = Layer.mergeAll(
  Logger.replace(Logger.defaultLogger, fileLogger),
  Logger.minimumLogLevel(LogLevel.Debug),
)

const waitForBackend = Effect.tryPromise(() =>
  fetch(`${CORTEX_URL}/health`).then((r) => { if (!r.ok) throw r }),
).pipe(
  Effect.retry({ times: 50, schedule: Schedule.spaced("200 millis") }),
  Effect.asVoid,
)

// ARCH: Backend readiness gate. Tools call this before hitting the HTTP API.
// Resolves once /health returns 200. Caches the result after first success.
let _backendReady: Promise<void> | null = null
const ensureBackend = (): Promise<void> => {
  if (_backendReady) return _backendReady
  _backendReady = (async () => {
    for (let i = 0; i < 60; i++) {
      try {
        const r = await fetch(`${CORTEX_URL}/health`)
        if (r.ok) return
      } catch { /* retry */ }
      await new Promise((r) => setTimeout(r, 250))
    }
    throw new Error("Backend did not become healthy within 15s")
  })()
  return _backendReady
}

// ARCH: MCP transport connects synchronously at startup — kiro-cli gets its
// initialize response before the backend is ready. Tool handlers gate on
// ensureBackend() so they work once the backend is up.
const connectMcp = Effect.async<never>(() => {
  const server = new McpServer({ name: "kiro-cortex", version: "0.1.0" })

  server.registerTool(
    "list_workflows",
    { description: "List available kiro-cortex workflows", inputSchema: z.object({}) },
    async () => {
      await ensureBackend()
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
      await ensureBackend()
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
      await ensureBackend()
      const res = await fetch(`${CORTEX_URL}/workflows/reload`, { method: "POST" })
      const data: unknown = await res.json()
      return { content: [{ type: "text" as const, text: JSON.stringify(data, null, 2) }] }
    },
  )

  const transport = new StdioServerTransport()
  server.connect(transport)
  // Never resume — MCP server runs until stdin closes
})

const program = Effect.gen(function* () {
  const isDebug = yield* Config.boolean("CORTEX_DEBUG").pipe(Config.withDefault(false))
  if (isDebug) yield* Effect.sync(() => writeFileSync(LOG_PATH, ""))
  yield* Effect.logInfo(`MCP startup — pid=${process.pid} cwd=${process.cwd()}`)
  yield* Effect.logDebug(`env: PGHOST=${process.env.PGHOST} PGPORT=${process.env.PGPORT} PGDATABASE=${process.env.PGDATABASE}`)

  // ARCH: Connect MCP transport FIRST — kiro-cli needs the initialize response
  // before its connection timeout fires. Backend starts in background; tools
  // gate on ensureBackend() internally.
  yield* connectMcp.pipe(Effect.fork)
  yield* Effect.logInfo("MCP transport forked")

  yield* main.pipe(Effect.fork)
  yield* Effect.logInfo("backend forked, waiting for health...")

  yield* waitForBackend.pipe(
    Effect.tapError((e) => Effect.logError(`health check failed: ${e}`)),
  )
  yield* Effect.logInfo("backend healthy — MCP tools ready")

  // Keep alive — both MCP transport and backend run in forked fibers
  yield* Effect.never
})

BunPlatform.BunRuntime.runMain(
  program.pipe(
    debug
      ? Effect.provide(DebugLoggerLive)
      : Logger.withMinimumLogLevel(LogLevel.None),
  ),
)
