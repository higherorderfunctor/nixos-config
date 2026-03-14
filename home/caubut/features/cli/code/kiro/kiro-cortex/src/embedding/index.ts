/**
 * @module embedding
 * Text-to-vector embedding via Ollama for pgvector similarity search.
 *
 * Provides a typed HTTP client for Ollama's /api/embed endpoint with
 * HttpApi + Schema validation. Converts instruction text into 768-dimensional
 * vectors (nomic-embed-text model) for storage and retrieval.
 *
 * Public API:
 * - {@link EmbeddingService} — Effect.Service wrapping the HttpApi client
 *
 * Used by: instruction/Loader (embedding at ingest time)
 *
 * EXTERNAL: Ollama server expected on localhost:11434
 * CONSTRAINT: Vector dimension 768 (nomic-embed-text). Changing model requires re-embedding.
 */

export { EmbeddingService } from "./Embedding.js"
