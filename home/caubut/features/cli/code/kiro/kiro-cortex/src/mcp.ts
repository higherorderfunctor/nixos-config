// ARCH: Pure Effect MCP server using @effect/ai. No HTTP server, no port, no
// race condition on agent switch. Tool handlers run Effects directly with full
// service access via layers. Set CORTEX_DEBUG=true to write logs to /tmp.
import { McpServer, Tool, Toolkit } from "@effect/ai"
import { BunSink, BunStream } from "@effect/platform-bun"
import * as BunPlatform from "@effect/platform-bun"
import { Data, Effect, Layer, Logger, LogLevel, Schema } from "effect"
import { SqlLive } from "./Sql.js"
import { layer as opaLayer } from "./opa/index.js"
import { layer as embeddingLayer } from "./embedding/index.js"
import { layer as instructionLayer, loadInstructions } from "./instruction/index.js"
import { registryLayer } from "./workflow/index.js"
import { buildMetaWorkflow } from "./meta-workflow/graph.js"
import { Command } from "@langchain/langgraph"
import { appendFileSync, writeFileSync } from "node:fs"

// ---------------------------------------------------------------------------
// Tools
// ---------------------------------------------------------------------------

const ListWorkflows = Tool.make("list_workflows", {
  description: "List available kiro-cortex workflows",
  success: Schema.String,
})

const RunWorkflow = Tool.make("run_workflow", {
  description: "Run a kiro-cortex workflow by ID",
  parameters: {
    id: Schema.String.annotations({ description: "Workflow ID" }),
    input: Schema.optional(Schema.Record({ key: Schema.String, value: Schema.Unknown })).annotations({ description: "Workflow input state" }),
    thread_id: Schema.optional(Schema.String).annotations({ description: "Thread ID for HITL resume" }),
  },
  success: Schema.String,
})

const ReloadWorkflows = Tool.make("reload_workflows", {
  description: "Reload workflow instructions from YAML files into the database. Use after editing workflow YAML files on disk.",
  success: Schema.String,
})

const CortexToolkit = Toolkit.make(ListWorkflows, RunWorkflow, ReloadWorkflows)

// ---------------------------------------------------------------------------
// Handlers
// ---------------------------------------------------------------------------

// ARCH: Lazy singleton — meta-workflow graph is built once on first invoke.
// eslint-disable-next-line @typescript-eslint/no-explicit-any
let _metaGraph: any = null
const getMetaGraph = async () => {
  if (!_metaGraph) _metaGraph = await buildMetaWorkflow()
  return _metaGraph
}

/** Tagged error for workflow execution failures. */
class WorkflowError extends Data.TaggedError("WorkflowError")<{
  readonly message: string
}> {}

const CortexToolHandlers = CortexToolkit.toLayer(
  Effect.gen(function* () {
    yield* loadInstructions
    yield* Effect.logInfo("Instructions loaded — MCP tools ready")

    // Inline reload: same logic as loadInstructions but with captured services
    const reload = Effect.provide(
      loadInstructions,
      Layer.mergeAll(instructionLayer, embeddingLayer).pipe(Layer.provide(SqlLive)),
    )

    return {
      list_workflows: () =>
        Effect.succeed(JSON.stringify([{
          id: "meta-workflow",
          name: "meta-workflow",
          description: "Build, update, and refine workflows",
        }], null, 2)),

      run_workflow: (params: {
        readonly id: string
        readonly input?: { readonly [x: string]: unknown } | undefined
        readonly thread_id?: string | undefined
      }) =>
        Effect.tryPromise({
          try: async () => {
            if (params.id !== "meta-workflow") throw new WorkflowError({ message: `Unknown workflow: ${params.id}` })
            const graph = await getMetaGraph()
            const tid = params.thread_id ?? crypto.randomUUID()
            const config = { configurable: { thread_id: tid } }
            // ARCH: thread_id present → HITL resume. The input becomes the
            // resume value returned by interrupt() in the paused node.
            const result = params.thread_id !== undefined
              ? await graph.invoke(new Command({ resume: params.input }), config)
              : await graph.invoke(params.input ?? {}, config)
            return JSON.stringify({ thread_id: tid, state: result }, null, 2)
          },
          catch: (e) => new WorkflowError({ message: e instanceof Error ? e.message : String(e) }),
        }).pipe(Effect.orDie),

      reload_workflows: () =>
        reload.pipe(
          Effect.map(() => JSON.stringify({ loaded: 0, message: "Workflow instructions reloaded from YAML" })),
          Effect.orDie,
        ),
    }
  }),
)

// ---------------------------------------------------------------------------
// Layer composition
// ---------------------------------------------------------------------------

const ServiceLive = Layer.mergeAll(
  opaLayer,
  embeddingLayer,
  instructionLayer,
  registryLayer,
).pipe(Layer.provideMerge(SqlLive))

const ServerLayer = McpServer.toolkit(CortexToolkit).pipe(
  Layer.provide(CortexToolHandlers),
  Layer.provide(McpServer.layerStdio({
    name: "kiro-cortex",
    version: "0.1.0",
    stdin: BunStream.stdin,
    stdout: BunSink.stdout,
  })),
  Layer.provide(ServiceLive),
)

// ---------------------------------------------------------------------------
// Debug logger (CORTEX_DEBUG=true → /tmp/kiro-cortex-mcp.log)
// ---------------------------------------------------------------------------

const LOG_PATH = "/tmp/kiro-cortex-mcp.log"
const debug = process.env.CORTEX_DEBUG === "true" || process.env.CORTEX_DEBUG === "1"

const fileLogger = Logger.make(({ message, date, logLevel }) => {
  appendFileSync(LOG_PATH, `${date.toISOString()} [${logLevel.label}] ${String(message)}\n`)
})

const DebugLoggerLive = Layer.mergeAll(
  Logger.replace(Logger.defaultLogger, fileLogger),
  Logger.minimumLogLevel(LogLevel.Debug),
)

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------

const program = Layer.launch(ServerLayer).pipe(
  debug
    ? Effect.provide(DebugLoggerLive)
    : Logger.withMinimumLogLevel(LogLevel.None),
)

if (debug) writeFileSync(LOG_PATH, "")

BunPlatform.BunRuntime.runMain(program, { disablePrettyLogger: true })
