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

export interface ScopingInput {
  readonly agent_role: string
  readonly task_type: string
  readonly domain: string
  readonly repo: string | null
}

export interface ScopingFilters {
  readonly allowed_domains: ReadonlyArray<string>
  readonly allowed_task_types: ReadonlyArray<string>
  readonly repo_filter: string | null
  readonly max_results: number
}

export class OpaService extends Effect.Service<OpaService>()("OpaService", {
  dependencies: [NodeHttpClient.layer],
  effect: Effect.gen(function* () {
    const client = yield* HttpClient.HttpClient

    const post = (url: string, input: unknown) =>
      Effect.gen(function* () {
        const request = HttpClientRequest.post(url)
        const requestWithBody = yield* HttpClientRequest.bodyJson({ input })(request)
        const response = yield* client.execute(requestWithBody)
        return yield* response.json
      }).pipe(
        Effect.mapError((error) => new OpaError({ message: String(error) })),
      )

    const evaluate = (query: OpaQuery): Effect.Effect<OpaDecision, OpaError> =>
      Effect.map(
        post("http://localhost:8181/v1/data/cortex/access/decision", query),
        (data: any) => data.result as OpaDecision,
      )

    const scope = (input: ScopingInput): Effect.Effect<ScopingFilters, OpaError> =>
      Effect.map(
        post("http://localhost:8181/v1/data/cortex/scoping/filters", input),
        (data: any) => data.result as ScopingFilters,
      )

    return { evaluate, scope } as const
  }),
}) {}
