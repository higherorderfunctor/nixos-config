import { Effect } from "effect"
import { HttpClient, HttpClientRequest } from "@effect/platform"
import { NodeHttpClient } from "@effect/platform-node"
import { EmbeddingError } from "./KiroContextError.js"

export class EmbeddingService extends Effect.Service<EmbeddingService>()("EmbeddingService", {
  dependencies: [NodeHttpClient.layer],
  effect: Effect.gen(function* () {
    const client = yield* HttpClient.HttpClient

    const embed = (text: string): Effect.Effect<ReadonlyArray<number>, EmbeddingError> =>
      Effect.gen(function* () {
        const request = HttpClientRequest.post("http://localhost:11434/api/embed")
        const requestWithBody = yield* HttpClientRequest.bodyJson({
          model: "nomic-embed-text",
          input: text,
        })(request)
        const response = yield* client.execute(requestWithBody)
        const data: any = yield* response.json
        return data.embeddings[0] as ReadonlyArray<number>
      }).pipe(
        Effect.mapError((e) => new EmbeddingError({ message: String(e) })),
      )

    return { embed } as const
  }),
}) {}
