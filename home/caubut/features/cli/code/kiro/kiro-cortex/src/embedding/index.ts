/**
 * @module embedding
 * Text-to-vector embedding via Ollama for pgvector similarity search.
 *
 * Provides a typed HTTP client for Ollama's /api/embed endpoint with
 * HttpApi + Schema validation. Schema.transform unwraps Ollama's batch response
 * to a single 768-dimensional vector (nomic-embed-text model).
 *
 * Public API:
 * - {@link EmbeddingClient} — Context.Tag for the HttpApi-derived client
 * - {@link layer} — Layer providing EmbeddingClient with NodeHttpClient
 * - {@link embed} — convenience function encapsulating model name
 * - {@link EmbeddingApiError} — TaggedError for Ollama error responses
 *
 * Used by: instruction/Loader (embedding at ingest time), index.ts (query embedding)
 *
 * EXTERNAL: Ollama server expected on localhost:11434
 * CONSTRAINT: Vector dimension 768 (nomic-embed-text). Changing model requires re-embedding.
 */

export { EmbeddingClient, EmbeddingApiError, layer, embed } from "./Embedding.js"
