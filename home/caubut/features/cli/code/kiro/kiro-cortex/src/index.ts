import { HttpApi, HttpApiBuilder, HttpApiEndpoint, HttpApiGroup, HttpMiddleware, HttpServer } from "@effect/platform"
import * as BunPlatform from "@effect/platform-bun"
import { Effect, Layer, Schema } from "effect"
import { SqlLive } from "./Sql.js"
import { OpaService } from "./Opa.js"
import { EmbeddingService } from "./Embedding.js"
import { InstructionRepo } from "./InstructionRepo.js"
import { BlockRegistry } from "./BlockRegistry.js"
import { createContextWorkflow, type ContextState } from "./Workflow.js"
import { TestError } from "./KiroContextError.js"

// --- Schemas ---

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

// --- Endpoints ---

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

// --- Groups ---

class HealthGroup extends HttpApiGroup.make("health")
  .add(HealthEndpoint)
{}

class ContextGroup extends HttpApiGroup.make("context")
  .add(ContextEndpoint)
{}

class WorkflowGroup extends HttpApiGroup.make("workflows")
  .add(WorkflowListEndpoint)
{}

class CortexApi extends HttpApi.make("cortex")
  .add(HealthGroup)
  .add(ContextGroup)
  .add(WorkflowGroup)
{}

// --- Handlers ---

const HealthApiLive = HttpApiBuilder.group(CortexApi, "health", (handlers) =>
  handlers.handle("check", () => Effect.succeed({ status: "ok" as const })),
)

const ContextApiLive = HttpApiBuilder.group(CortexApi, "context", (handlers) =>
  handlers.handle("context", ({ payload }) =>
    Effect.gen(function* () {
      // 1. OPA access control
      const opa = yield* OpaService
      const opaDecision = yield* opa.evaluate({
        user_id: payload.user_id,
        query: payload.query,
      }).pipe(Effect.mapError((e) => new TestError({ message: e.message })))

      if (!opaDecision.allowed) {
        return {
          allowed: false,
          reason: opaDecision.reason,
          instructions: [],
          assembled_context: null,
          token_count: 0,
        }
      }

      // 2. Embed query
      const embedding = yield* EmbeddingService
      const queryVec = yield* embedding.embed(payload.query).pipe(
        Effect.mapError((e) => new TestError({ message: e.message })),
      )

      // 3. Search instructions
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

      // 4. Assemble context via workflow
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

// --- Server ---

const WorkflowApiLive = HttpApiBuilder.group(CortexApi, "workflows", (handlers) =>
  handlers.handle("list", () =>
    Effect.gen(function* () {
      const registry = yield* BlockRegistry
      // Return pipelines (none registered yet — populated in 4.4)
      void registry
      return [] as ReadonlyArray<{ id: string; name: string; description: string }>
    }),
  ),
)

const ApiLive = HttpApiBuilder.api(CortexApi).pipe(
  Layer.provide(Layer.mergeAll(HealthApiLive, ContextApiLive, WorkflowApiLive)),
)

const HttpLive = HttpApiBuilder.serve(HttpMiddleware.logger).pipe(
  Layer.provide(ApiLive),
  Layer.provide(OpaService.Default),
  Layer.provide(EmbeddingService.Default),
  Layer.provide(InstructionRepo.Default),
  Layer.provide(BlockRegistry.Default),
  Layer.provide(SqlLive),
  HttpServer.withLogAddress,
  Layer.provide(BunPlatform.BunHttpServer.layer({ port: 3100 })),
)

HttpLive.pipe(Layer.launch, BunPlatform.BunRuntime.runMain)
