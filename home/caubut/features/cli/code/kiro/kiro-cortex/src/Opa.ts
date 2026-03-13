import { Effect } from "effect"
import { HttpClient, HttpClientRequest } from "@effect/platform"
import { NodeHttpClient } from "@effect/platform-node"
import { OpaError } from "./KiroContextError.js"

export interface OpaDecision {
  allowed: boolean
  denied: boolean
  reason: string
}

export interface OpaQuery {
  user_id: string
  query: string
}

export class OpaService extends Effect.Service<OpaService>()("OpaService", {
  dependencies: [NodeHttpClient.layer],
  effect: Effect.gen(function* () {
    const client = yield* HttpClient.HttpClient

    const evaluate = (query: OpaQuery): Effect.Effect<OpaDecision, OpaError> =>
      Effect.gen(function* () {
        const request = HttpClientRequest.post("http://localhost:8181/v1/data/cortex/test/decision")
        const requestWithBody = yield* HttpClientRequest.bodyJson({ input: query })(request)
        const response = yield* client.execute(requestWithBody)
        const data: any = yield* response.json
        return data.result as OpaDecision
      }).pipe(
        Effect.mapError((error) => new OpaError({ message: String(error) })),
      )

    return { evaluate } as const
  }),
}) {}
