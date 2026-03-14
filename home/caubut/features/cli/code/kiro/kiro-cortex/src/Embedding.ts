/**
 * @module Embedding
 * Embedding service for converting text to vector representations via Ollama.
 *
 * ARCH: Uses HttpApi + Schema to define the Ollama embed API shape, then derives
 * a fully typed client via HttpApiClient.make(). No `as any` casts — the response
 * schema models what Ollama actually returns (array of embedding arrays).
 *
 * EXTERNAL: Ollama returns `{ embeddings: number[][] }` — an array of arrays because
 * the API supports batch embedding. We always send a single input and take `[0]`.
 */

import { Effect, Schema } from "effect"
import {
  HttpApi,
  HttpApiClient,
  HttpApiEndpoint,
  HttpApiGroup,
} from "@effect/platform"
import { NodeHttpClient } from "@effect/platform-node"
import { EmbeddingError } from "./KiroContextError.js"

// ---------------------------------------------------------------------------
// Schemas — model the real Ollama API shapes honestly
// ---------------------------------------------------------------------------

/** Request body for Ollama's /api/embed endpoint. */
const EmbedRequest = Schema.Struct({
  model: Schema.String,
  input: Schema.String,
})

/**
 * Response from Ollama's /api/embed endpoint.
 * EXTERNAL: Returns array of arrays — one embedding per input string.
 * We send a single input, so embeddings[0] is our vector.
 */
const EmbedResponse = Schema.Struct({
  embeddings: Schema.Array(Schema.Array(Schema.Number)),
})

// ---------------------------------------------------------------------------
// HttpApi definition — describes the Ollama embed API shape
// ---------------------------------------------------------------------------

const EmbedEndpoint = HttpApiEndpoint.post("embed")`/api/embed`
  .setPayload(EmbedRequest)
  .addSuccess(EmbedResponse)

class OllamaGroup extends HttpApiGroup.make("ollama")
  .add(EmbedEndpoint)
{}

class OllamaApi extends HttpApi.make("ollamaApi").add(OllamaGroup) {}

// ---------------------------------------------------------------------------
// Service — typed Ollama embedding client
// ---------------------------------------------------------------------------

/**
 * Embedding service that converts text to 768-dimensional vectors via Ollama.
 *
 * ARCH: Uses nomic-embed-text model (768 dimensions). Model is pinned — if changed,
 * all existing vectors in pgvector must be re-embedded for consistency.
 *
 * CONSTRAINT: Model name is hardcoded here. If we support multiple models in the
 * future, this becomes a configuration parameter.
 */
export class EmbeddingService extends Effect.Service<EmbeddingService>()("EmbeddingService", {
  dependencies: [NodeHttpClient.layer],
  effect: Effect.gen(function* () {
    const client = yield* HttpApiClient.make(OllamaApi, {
      baseUrl: "http://localhost:11434",
    })

    /**
     * Embed a text string into a vector representation.
     * @param text - The text to embed.
     * @returns 768-dimensional vector from nomic-embed-text.
     */
    const embed = (text: string): Effect.Effect<ReadonlyArray<number>, EmbeddingError> =>
      client.ollama.embed({
        payload: { model: "nomic-embed-text", input: text },
      }).pipe(
        // EXTERNAL: Ollama returns array of arrays (batch support). We send one input → take [0].
        Effect.map((response) => response.embeddings[0]!),
        Effect.mapError((error) => new EmbeddingError({ message: String(error) })),
      )

    return { embed } as const
  }),
}) {}
