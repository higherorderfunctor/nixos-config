import { HttpApi, HttpApiBuilder, HttpApiEndpoint, HttpApiGroup, HttpMiddleware, HttpServer } from "@effect/platform"
import * as BunPlatform from "@effect/platform-bun"
import { Effect, Layer, Schema } from "effect"
import { SqlLive } from "./Sql.js"

const HealthResponse = Schema.Struct({ status: Schema.Literal("ok") })

const HealthEndpoint = HttpApiEndpoint.make("GET")("check", "/health")
  .addSuccess(HealthResponse)

class HealthGroup extends HttpApiGroup.make("health")
  .add(HealthEndpoint)
{}

class CortexApi extends HttpApi.make("cortex")
  .add(HealthGroup)
{}

const HealthApiLive = HttpApiBuilder.group(CortexApi, "health", (handlers) =>
  handlers.handle("check", () => Effect.succeed({ status: "ok" as const })),
)

const ApiLive = Layer.provide(HttpApiBuilder.api(CortexApi), HealthApiLive)

const HttpLive = HttpApiBuilder.serve(HttpMiddleware.logger).pipe(
  Layer.provide(ApiLive),
  Layer.provide(SqlLive),
  HttpServer.withLogAddress,
  Layer.provide(BunPlatform.BunHttpServer.layer({ port: 3100 })),
)

HttpLive.pipe(Layer.launch, BunPlatform.BunRuntime.runMain)
