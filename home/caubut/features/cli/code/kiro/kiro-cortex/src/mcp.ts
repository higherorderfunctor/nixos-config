// ARCH: Single Effect program — forks the HTTP backend, waits for it to be
// ready, then connects the MCP stdio transport. All logging suppressed so
// stdout stays clean for JSON-RPC. Set CORTEX_DEBUG=true to write logs to /tmp.
import { main } from "./main.js"
import { Config, Effect, Layer, Logger, LogLevel, Schedule } from "effect"
import * as BunPlatform from "@effect/platform-bun"
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js"
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js"
import { z } from "zod"
import { appendFileSync, writeFileSync } from "node:fs"

const CORTEX_URL = "http://localhost:3100"
const LOG_PATH = "/tmp/kiro-cortex-mcp.log"

// ARCH: File logger for MCP diagnostics. Writes to /tmp so it works regardless
// of cwd. Gated behind CORTEX_DEBUG env var — off by default.
const fileLogger = Logger.make(({ message, date, logLevel }) => {
  appendFileSync(LOG_PATH, `${date.toISOString()} [${logLevel.label}] ${String(message)}\n`)
})

// ARCH: Logger layer is a bootstrap concern — must be resolved before the
// Effect program runs. Logger.withMinimumLogLevel (Effect combinator) is the
// only reliable way to suppress stdout with BunRuntime.runMain. Logger.replace
// via Layer doesn't fully override the runtime's default logger. When debug is
// on, stdout leaking is acceptable — the file logger is the diagnostic target.
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
  const isDebug = yield* Config.boolean("CORTEX_DEBUG").pipe(Config.withDefault(false))
  if (isDebug) yield* Effect.sync(() => writeFileSync(LOG_PATH, ""))
  yield* Effect.logInfo(`MCP startup — pid=${process.pid} cwd=${process.cwd()}`)
  yield* Effect.logDebug(`env: PATH=${process.env.PATH?.slice(0, 200)}`)
  yield* Effect.logDebug(`env: PGHOST=${process.env.PGHOST} PGPORT=${process.env.PGPORT} PGDATABASE=${process.env.PGDATABASE} DATABASE_URL=${process.env.DATABASE_URL}`)
  yield* main.pipe(Effect.fork)
  yield* Effect.logInfo("backend forked, waiting for health...")
  yield* waitForBackend.pipe(
    Effect.tapError((e) => Effect.logError(`health check failed: ${e}`)),
  )
  yield* Effect.logInfo("backend healthy, connecting MCP transport...")
  yield* startMcp
})

BunPlatform.BunRuntime.runMain(
  program.pipe(
    debug
      ? Effect.provide(DebugLoggerLive)
      : Logger.withMinimumLogLevel(LogLevel.None),
  ),
)
