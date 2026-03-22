// ARCH: Generic MCP server factory. Agent packages call startMcpServer() with
// their workflows. No workflow-specific imports — agents register via WorkflowDef.
import { McpServer, Tool, Toolkit } from "@effect/ai"
import { BunSink, BunStream } from "@effect/platform-bun"
import * as BunPlatform from "@effect/platform-bun"
import { Data, Effect, Inspectable, Layer, Logger, LogLevel, Schema, Cause, flow } from "effect"
import { SqlLive } from "./Sql.js"
import { layer as opaLayer } from "./opa/index.js"
import { layer as embeddingLayer } from "./embedding/index.js"
import { layer as instructionLayer, loadInstructions } from "./instruction/index.js"
import { registryLayer } from "./workflow/index.js"
import { Command, isInterrupted, INTERRUPT } from "@langchain/langgraph"
import { appendFileSync, writeFileSync } from "node:fs"

/** Workflow registration — agent packages provide these. */
export interface WorkflowDef {
  readonly id: string
  readonly name: string
  readonly description: string
  readonly build: () => Promise<unknown>
}

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

/** Tagged error for workflow execution failures. */
class WorkflowError extends Data.TaggedError("WorkflowError")<{
  readonly message: string
}> {}

// ---------------------------------------------------------------------------
// Server factory
// ---------------------------------------------------------------------------

/**
 * Start the kiro-cortex MCP stdio server with registered workflows.
 * Called by agent packages as their entry point.
 */
export const startMcpServer = (workflows: ReadonlyArray<WorkflowDef>): void => {
  // Lazy graph cache per workflow
  const graphCache = new Map<string, unknown>()
  const getGraph = async (def: WorkflowDef) => {
    let g = graphCache.get(def.id)
    if (!g) { g = await def.build(); graphCache.set(def.id, g) }
    return g as { invoke: (input: unknown, config: unknown) => Promise<unknown> }
  }

  const CortexToolHandlers = CortexToolkit.toLayer(
    Effect.gen(function* () {
      yield* loadInstructions
      yield* Effect.logInfo("Instructions loaded — MCP tools ready")

      const reload = Effect.provide(
        loadInstructions,
        Layer.mergeAll(instructionLayer, embeddingLayer).pipe(Layer.provide(SqlLive)),
      )

      return {
        list_workflows: () =>
          Effect.succeed(JSON.stringify(
            workflows.map((w) => ({ id: w.id, name: w.name, description: w.description })),
            null, 2,
          )),

        run_workflow: (params: {
          readonly id: string
          readonly input?: { readonly [x: string]: unknown } | undefined
          readonly thread_id?: string | undefined
        }) =>
          Effect.tryPromise({
            try: async () => {
              const def = workflows.find((w) => w.id === params.id)
              if (!def) throw new WorkflowError({ message: `Unknown workflow: ${params.id}` })
              const graph = await getGraph(def)
              const tid = params.thread_id ?? crypto.randomUUID()
              const config = { configurable: { thread_id: tid } }
              // ARCH: On resume, unwrap resume_value if present — MCP input schema
              // forces Record<string, unknown> but interrupt answers can be any type.
              const resumeValue = params.input?.resume_value ?? params.input
              const result = params.thread_id !== undefined
                ? await graph.invoke(new Command({ resume: resumeValue }), config)
                : await graph.invoke(params.input ?? {}, config)

              // ARCH (5.7.1): Surface interrupt payloads so Claude sees what blocks are asking.
              // LangGraph embeds interrupt values in the returned state via INTERRUPT symbol.
              const interrupts = isInterrupted(result)
                ? (result as Record<symbol, Array<{ value?: unknown }>>)[INTERRUPT].map((i) => i.value)
                : []

              return JSON.stringify({ thread_id: tid, state: result, interrupts }, null, 2)
            },
            catch: (e) => new WorkflowError({ message: e instanceof Error ? e.message : String(e) }),
          }).pipe(
            Effect.sandbox,
            Effect.catchAll((cause) =>
              Effect.logError(Cause.pretty(cause)).pipe(
                Effect.map(() => JSON.stringify({ error: Cause.pretty(cause) })),
              ),
            ),
          ),

        reload_workflows: () =>
          reload.pipe(
            Effect.map(() => JSON.stringify({ loaded: 0, message: "Workflow instructions reloaded from YAML" })),
            Effect.sandbox,
            Effect.catchAll((cause) =>
              Effect.logError(Cause.pretty(cause)).pipe(
                Effect.map(() => JSON.stringify({ error: Cause.pretty(cause) })),
              ),
            ),
          ),
      }
    }),
  )

  const ServiceLive = Layer.mergeAll(
    opaLayer, embeddingLayer, instructionLayer, registryLayer,
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

  // Debug logger
  const LOG_PATH = "/tmp/kiro-cortex-mcp.log"
  const debug = process.env.CORTEX_DEBUG === "true" || process.env.CORTEX_DEBUG === "1"

  const fileLogger = Logger.make(({ message, date, logLevel, cause }) => {
    const causeStr = cause && Cause.pretty(cause) !== "" ? ` cause=${Cause.pretty(cause)}` : ""
    appendFileSync(LOG_PATH, `${date.toISOString()} [${logLevel.label}] ${Inspectable.toStringUnknown(message)}${causeStr}\n`)
  })

  const DebugLoggerLive = Layer.mergeAll(
    Logger.replace(Logger.defaultLogger, fileLogger),
    Logger.minimumLogLevel(LogLevel.Debug),
  )

  const program = Layer.launch(ServerLayer).pipe(
    Effect.tapError(flow(Inspectable.toStringUnknown, Effect.logError)),
    Effect.tapDefect(flow(Inspectable.toStringUnknown, Effect.logFatal)),
    debug
      ? Effect.provide(DebugLoggerLive)
      : Logger.withMinimumLogLevel(LogLevel.None),
  )

  if (debug) writeFileSync(LOG_PATH, "")

  BunPlatform.BunRuntime.runMain(program, { disablePrettyLogger: true })
}
