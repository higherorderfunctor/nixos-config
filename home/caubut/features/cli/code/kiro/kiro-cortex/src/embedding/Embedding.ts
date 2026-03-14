/**
 * @module Embedding
 * Ollama embedding client for converting text to vector representations.
 *
 * ARCH: Uses HttpApi + Schema to define the Ollama embed API shape, then derives
 * a fully typed client via HttpApiClient.make(). Schema.transform unwraps Ollama's
 * `{ embeddings: number[][] }` to a single `ReadonlyArray<number>`.
 *
 * ARCH: Uses Context.Tag + Layer.effect (not Effect.Service) because this is a
 * pure HTTP client derived from HttpApiClient.make.
 *
 * EXTERNAL: Ollama returns `{ embeddings: number[][] }` — an array of arrays because
 * the API supports batch embedding. We always send a single input and take `[0]`.
 *
 * EXTERNAL: Ollama server expected on localhost:11434.
 * CONSTRAINT: Model is nomic-embed-text (768 dimensions). Changing model requires re-embedding.
 */

import { Context, Effect, Layer, Schema } from "effect"
import {
  HttpApi,
  HttpApiClient,
  HttpApiEndpoint,
  HttpApiGroup,
} from "@effect/platform"
import { NodeHttpClient } from "@effect/platform-node"

// ---------------------------------------------------------------------------
// Error schema
// ---------------------------------------------------------------------------

/**
 * Embedding API error — models Ollama's `{ error: string }` response.
 *
 * EXTERNAL: Ollama returns this shape on error responses.
 * Schema.transform maps from wire format (no _tag) to TaggedError.
 */
export class EmbeddingApiError extends Schema.TaggedError<EmbeddingApiError>()("EmbeddingApiError", {
  message: Schema.String,
}) {}

/** EXTERNAL: Transform Ollama's `{ error: string }` → EmbeddingApiError. */
const EmbeddingApiErrorFromWire = Schema.transform(
  Schema.Struct({ error: Schema.String }),
  Schema.typeSchema(EmbeddingApiError),
  {
    decode: (wire) => new EmbeddingApiError({ message: wire.error }),
    encode: (err) => ({ error: err.message }),
  },
)

// ---------------------------------------------------------------------------
// Success schema — unwrap Ollama's batch response to single vector
// ---------------------------------------------------------------------------

/**
 * EXTERNAL: Schema.transform unwraps `{ embeddings: number[][] }` → `ReadonlyArray<number>`.
 * NonEmptyArray guarantees `[0]` exists — Ollama always returns at least one for single input.
 */
const EmbedSuccess = Schema.transform(
  Schema.Struct({ embeddings: Schema.NonEmptyArray(Schema.Array(Schema.Number)) }),
  Schema.Array(Schema.Number),
  {
    strict: true,
    decode: (wire) => wire.embeddings[0],
    encode: (domain) => ({ embeddings: [domain] as const }),
  },
)

// ---------------------------------------------------------------------------
// HttpApi definition
// ---------------------------------------------------------------------------

const EmbedRequest = Schema.Struct({
  model: Schema.String,
  input: Schema.String,
})

const EmbedEndpoint = HttpApiEndpoint.post("embed")`/api/embed`
  .setPayload(EmbedRequest)
  .addSuccess(EmbedSuccess)
  .addError(EmbeddingApiErrorFromWire, { status: 400 })

class OllamaGroup extends HttpApiGroup.make("ollama")
  .add(EmbedEndpoint)
{}

class OllamaApi extends HttpApi.make("ollamaApi").add(OllamaGroup) {}

// ---------------------------------------------------------------------------
// Context.Tag + Layer
// ---------------------------------------------------------------------------

const make = HttpApiClient.make(OllamaApi, {
  baseUrl: "http://localhost:11434",
})

/**
 * Embedding client tag for dependency injection.
 *
 * ARCH: Uses Context.Tag + Layer.effect (not Effect.Service) because this is a
 * pure HTTP client derived from HttpApiClient.make.
 */
export class EmbeddingClient extends Context.Tag("EmbeddingClient")<
  EmbeddingClient,
  Effect.Effect.Success<typeof make>
>() {}

/** Embedding client layer. Provides EmbeddingClient with NodeHttpClient. */
export const layer = Layer.effect(EmbeddingClient, make).pipe(
  Layer.provide(NodeHttpClient.layer),
)

// ---------------------------------------------------------------------------
// Convenience — encapsulates model name
// ---------------------------------------------------------------------------

/**
 * Embed text using nomic-embed-text model.
 *
 * CONSTRAINT: Model name pinned here. Changing model requires re-embedding all instructions.
 */
export const embed = (text: string) =>
  Effect.flatMap(EmbeddingClient, (client) =>
    client.ollama.embed({ payload: { model: "nomic-embed-text", input: text } }),
  )
