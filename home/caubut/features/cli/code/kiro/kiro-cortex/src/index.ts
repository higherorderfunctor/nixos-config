import { HttpApi, HttpApiBuilder, HttpApiEndpoint, HttpApiGroup, HttpMiddleware, HttpServer } from "@effect/platform"
import * as BunPlatform from "@effect/platform-bun"
import { Effect, Layer, Schema } from "effect"
import { SqlLive } from "./Sql.js"
import { OpaService } from "./Opa.js"
import { createTestWorkflow } from "./Workflow.js"
import { TestError } from "./KiroContextError.js"

const HealthResponse = Schema.Struct({ status: Schema.Literal("ok") })

const HealthEndpoint = HttpApiEndpoint.make("GET")("check", "/health")
  .addSuccess(HealthResponse)

const TestRequest = Schema.Struct({
  query: Schema.String,
  user_id: Schema.String,
})

const TestResponse = Schema.Struct({
  opa_decision: Schema.Struct({
    allowed: Schema.Boolean,
    denied: Schema.Boolean,
    reason: Schema.String,
  }),
  workflow_result: Schema.Any,
})

const TestEndpoint = HttpApiEndpoint.make("POST")("test", "/test")
  .addSuccess(TestResponse)
  .setPayload(TestRequest)
  .addError(TestError, { status: 500 })

class HealthGroup extends HttpApiGroup.make("health")
  .add(HealthEndpoint)
{}

class TestGroup extends HttpApiGroup.make("test")
  .add(TestEndpoint)
{}

class CortexApi extends HttpApi.make("cortex")
  .add(HealthGroup)
  .add(TestGroup)
{}

const HealthApiLive = HttpApiBuilder.group(CortexApi, "health", (handlers) =>
  handlers.handle("check", () => Effect.succeed({ status: "ok" as const })),
)

const runWorkflow = (query: string, user_id: string) =>
  Effect.tryPromise({
    try: () =>
      createTestWorkflow().invoke({
        query,
        user_id,
        policy_decision: null,
        vector_results: null,
        context: null,
        response: null,
      }),
    catch: (e) => new TestError({ message: String(e) }),
  })

const TestApiLive = HttpApiBuilder.group(CortexApi, "test", (handlers) =>
  handlers.handle("test", ({ payload }) =>
    Effect.gen(function* () {
      const opa = yield* OpaService
      const opaDecision = yield* opa.evaluate({
        user_id: payload.user_id,
        query: payload.query,
      }).pipe(Effect.mapError((e) => new TestError({ message: e.message })))

      const workflowResult = yield* runWorkflow(payload.query, payload.user_id)

      return {
        opa_decision: opaDecision,
        workflow_result: workflowResult,
      }
    }),
  ),
)

const ApiLive = HttpApiBuilder.api(CortexApi).pipe(
  Layer.provide(Layer.mergeAll(HealthApiLive, TestApiLive)),
)

const HttpLive = HttpApiBuilder.serve(HttpMiddleware.logger).pipe(
  Layer.provide(ApiLive),
  Layer.provide(OpaService.Default),
  Layer.provide(SqlLive),
  HttpServer.withLogAddress,
  Layer.provide(BunPlatform.BunHttpServer.layer({ port: 3100 })),
)

HttpLive.pipe(Layer.launch, BunPlatform.BunRuntime.runMain)
