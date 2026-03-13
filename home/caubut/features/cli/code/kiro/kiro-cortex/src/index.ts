import { HttpApi, HttpApiBuilder, HttpApiEndpoint, HttpApiGroup } from "@effect/platform";
import * as BunPlatform from "@effect/platform-bun";
import { Effect, Layer, Schema } from "effect";

const HealthResponse = Schema.Struct({ status: Schema.Literal("ok") });

class HealthApi extends HttpApiGroup.make("health").pipe(
  HttpApiGroup.add(
    HttpApiEndpoint.get("check", "/health").pipe(
      HttpApiEndpoint.setSuccess(HealthResponse),
    ),
  ),
) {}

class CortexApi extends HttpApi.make("cortex").pipe(HttpApi.addGroup(HealthApi)) {}

const HealthApiLive = HttpApiBuilder.group(CortexApi, "health", (handlers) =>
  handlers.pipe(
    HttpApiBuilder.handle("check", () => Effect.succeed({ status: "ok" as const })),
  ),
);

const ApiLive = HttpApiBuilder.api(CortexApi).pipe(Layer.provide(HealthApiLive));

const ServerLive = HttpApiBuilder.serve().pipe(
  Layer.provide(ApiLive),
  Layer.provide(BunPlatform.BunHttpServer.layer({ port: 3100 })),
);

Layer.launch(ServerLive).pipe(
  Effect.tapErrorCause(Effect.logError),
  BunPlatform.BunRuntime.runMain,
);
