/**
 * @module index
 * HTTP API server for kiro-cortex — the main entry point.
 *
 * ARCH: Uses @effect/platform HttpApi for type-safe endpoint definitions with
 * Schema validation on request/response bodies. The server provides three groups:
 * - health: liveness check
 * - context: Phase 3 RAG loop (OPA → embed → pgvector → assemble)
 * - workflows: list and invoke registered workflows (meta-workflow)
 *
 * ARCH: At startup, the YAML instruction loader runs before the HTTP server
 * begins accepting requests, ensuring seed instructions are in pgvector.
 */

import { HttpApi, HttpApiBuilder, HttpApiEndpoint, HttpApiGroup, HttpMiddleware, HttpServer } from "@effect/platform"
import * as BunPlatform from "@effect/platform-bun"
import { Effect, Layer, Schema } from "effect"
import { SqlLive } from "./Sql.js"
import { OpaClient, OpaApiError, layer as opaLayer } from "./opa/index.js"
import { embed as embedText, layer as embeddingLayer } from "./embedding/index.js"
import { InstructionRepo, layer as instructionLayer } from "./instruction/index.js"
import { BlockRegistry, registryLayer } from "./workflow/index.js"
import { createContextWorkflow, type ContextState } from "./workflow/index.js"
import { buildMetaWorkflow } from "./meta-workflow/graph.js"
import { loadInstructions } from "./instruction/index.js"
import { Command } from "@langchain/langgraph"

// ---------------------------------------------------------------------------
// Errors — co-located with the HTTP server that uses them
// ---------------------------------------------------------------------------

/** HTTP API handler errors (used by endpoint handlers). */
class TestError extends Schema.TaggedError<TestError>()(
  "TestError",
  { message: Schema.String },
) {}

// ---------------------------------------------------------------------------
// Schemas — request/response types for HTTP endpoints
// ---------------------------------------------------------------------------

const HealthResponse = Schema.Struct({ status: Schema.Literal("ok") })

const ContextRequest = Schema.Struct({
  query: Schema.String,
  user_id: Schema.String,
  agent_role: Schema.optionalWith(Schema.String, { default: () => "developer" }),
  task_type: Schema.optionalWith(Schema.String, { default: () => "coding" }),
  domain: Schema.optionalWith(Schema.String, { default: () => "" }),
  token_budget: Schema.optionalWith(Schema.Number, { default: () => 4000 }),
})

const InstructionResult = Schema.Struct({
  id: Schema.String,
  text: Schema.String,
  priority: Schema.NullOr(Schema.String),
  distance: Schema.Number,
})

const ContextResponse = Schema.Struct({
  allowed: Schema.Boolean,
  reason: Schema.String,
  instructions: Schema.Array(InstructionResult),
  assembled_context: Schema.NullOr(Schema.String),
  token_count: Schema.Number,
})

// ---------------------------------------------------------------------------
// Endpoints
// ---------------------------------------------------------------------------

const HealthEndpoint = HttpApiEndpoint.make("GET")("check", "/health")
  .addSuccess(HealthResponse)

const ContextEndpoint = HttpApiEndpoint.make("POST")("context", "/context")
  .addSuccess(ContextResponse)
  .setPayload(ContextRequest)
  .addError(TestError, { status: 500 })

// --- Workflow Endpoints ---

const WorkflowItem = Schema.Struct({
  id: Schema.String,
  name: Schema.String,
  description: Schema.String,
})

const WorkflowListResponse = Schema.Array(WorkflowItem)

const WorkflowListEndpoint = HttpApiEndpoint.make("GET")("list", "/workflows")
  .addSuccess(WorkflowListResponse)

const WorkflowInvokeRequest = Schema.Struct({
  input: Schema.optionalWith(Schema.Record({ key: Schema.String, value: Schema.Unknown }), { default: () => ({}) }),
  thread_id: Schema.optionalWith(Schema.String, { default: () => crypto.randomUUID() }),
  resume: Schema.optionalWith(Schema.Unknown, { default: () => undefined }),
})

const WorkflowInvokeResponse = Schema.Struct({
  thread_id: Schema.String,
  state: Schema.Record({ key: Schema.String, value: Schema.Unknown }),
})

const WorkflowInvokeEndpoint = HttpApiEndpoint.make("POST")("invoke", "/workflows/:id/invoke")
  .setPath(Schema.Struct({ id: Schema.String }))
  .setPayload(WorkflowInvokeRequest)
  .addSuccess(WorkflowInvokeResponse)
  .addError(TestError, { status: 500 })

// ---------------------------------------------------------------------------
// Groups + API
// ---------------------------------------------------------------------------

class HealthGroup extends HttpApiGroup.make("health")
  .add(HealthEndpoint)
{}

class ContextGroup extends HttpApiGroup.make("context")
  .add(ContextEndpoint)
{}

class WorkflowGroup extends HttpApiGroup.make("workflows")
  .add(WorkflowListEndpoint)
  .add(WorkflowInvokeEndpoint)
{}

class CortexApi extends HttpApi.make("cortex")
  .add(HealthGroup)
  .add(ContextGroup)
  .add(WorkflowGroup)
{}

// ---------------------------------------------------------------------------
// Handlers — implement the API endpoints
// ---------------------------------------------------------------------------

const HealthApiLive = HttpApiBuilder.group(CortexApi, "health", (handlers) =>
  handlers.handle("check", () => Effect.succeed({ status: "ok" as const })),
)

const ContextApiLive = HttpApiBuilder.group(CortexApi, "context", (handlers) =>
  handlers.handle("context", ({ payload }) =>
    Effect.gen(function* () {
      // --- Step 1: OPA access control ---
      const opa = yield* OpaClient
      const opaDecision = yield* opa.opa.evaluate({
        payload: { input: { user_id: payload.user_id, query: payload.query } },
      }).pipe(Effect.mapError((e) => new TestError({ message: e instanceof OpaApiError ? e.message : String(e) })))

      if (!opaDecision.allowed) {
        return {
          allowed: false,
          reason: opaDecision.reason,
          instructions: [],
          assembled_context: null,
          token_count: 0,
        }
      }

      // --- Step 2: Embed query via Ollama ---
      const queryVec = yield* embedText(payload.query).pipe(
        Effect.mapError((e) => new TestError({ message: String(e) })),
      )

      // --- Step 3: Search pgvector for relevant instructions ---
      const repo = yield* InstructionRepo
      const instructions = yield* repo.search(
        queryVec,
        {
          domain: payload.domain || undefined,
          agent_role: payload.agent_role,
          task_type: payload.task_type,
        },
        20,
      ).pipe(Effect.mapError((e) => new TestError({ message: e.message })))

      // --- Step 4: Assemble context via LangGraph workflow ---
      const workflow = createContextWorkflow()
      const result = yield* Effect.tryPromise({
        try: () => workflow.invoke({
          query: payload.query,
          user_id: payload.user_id,
          agent_role: payload.agent_role,
          task_type: payload.task_type,
          domain: payload.domain,
          token_budget: payload.token_budget,
          policy_decision: opaDecision,
          instructions: instructions.map((i) => ({
            id: i.id,
            text: i.text,
            priority: i.priority,
            distance: i.distance,
          })),
          assembled_context: null,
          token_count: 0,
        } satisfies ContextState),
        catch: (e) => new TestError({ message: String(e) }),
      })

      return {
        allowed: true,
        reason: "allowed",
        instructions: instructions.map((i) => ({
          id: i.id,
          text: i.text,
          priority: i.priority,
          distance: i.distance,
        })),
        assembled_context: result.assembled_context ?? null,
        token_count: result.token_count ?? 0,
      }
    }),
  ),
)

// ---------------------------------------------------------------------------
// Server — layer composition and startup
// ---------------------------------------------------------------------------

// ARCH: Lazy singleton — meta-workflow graph is built once on first invoke.
// eslint-disable-next-line @typescript-eslint/no-explicit-any -- CompiledStateGraph generic params are dynamic
let _metaGraph: any = null
const getMetaGraph = async () => {
  if (!_metaGraph) _metaGraph = await buildMetaWorkflow()
  return _metaGraph
}

const WorkflowApiLive = HttpApiBuilder.group(CortexApi, "workflows", (handlers) =>
  handlers
    .handle("list", () =>
      Effect.gen(function* () {
        const registry = yield* BlockRegistry
        void registry
        return [{
          id: "meta-workflow",
          name: "meta-workflow",
          description: "Build, update, and refine workflows",
        }] as ReadonlyArray<{ id: string; name: string; description: string }>
      }),
    )
    .handle("invoke", ({ path, payload }) =>
      Effect.tryPromise({
        try: async () => {
          if (path.id !== "meta-workflow") throw new Error(`Unknown workflow: ${path.id}`)
          const graph = await getMetaGraph()
          const config = { configurable: { thread_id: payload.thread_id } }
          const result = payload.resume !== undefined
            ? await graph.invoke(new Command({ resume: payload.resume }), config)
            : await graph.invoke(payload.input, config)
          return {
            thread_id: payload.thread_id,
            state: result as Record<string, unknown>,
          }
        },
        catch: (e) => new TestError({ message: String(e) }),
      }),
    ),
)

const ApiLive = HttpApiBuilder.api(CortexApi).pipe(
  Layer.provide(Layer.mergeAll(HealthApiLive, ContextApiLive, WorkflowApiLive)),
)

const HttpLive = HttpApiBuilder.serve(HttpMiddleware.logger).pipe(
  Layer.provide(ApiLive),
  Layer.provide(opaLayer),
  Layer.provide(embeddingLayer),
  Layer.provide(instructionLayer),
  Layer.provide(registryLayer),
  Layer.provide(SqlLive),
  HttpServer.withLogAddress,
  Layer.provide(BunPlatform.BunHttpServer.layer({ port: 3100 })),
)

// ARCH: Loader runs before server — reads seed YAML, embeds, upserts to pgvector.
// Uses separate service instances (acceptable for one-time startup task).
const LoaderDeps = Layer.mergeAll(
  embeddingLayer,
  instructionLayer,
).pipe(Layer.provide(SqlLive))

const main = loadInstructions.pipe(
  Effect.provide(LoaderDeps),
  Effect.andThen(Layer.launch(HttpLive)),
)

BunPlatform.BunRuntime.runMain(main)
