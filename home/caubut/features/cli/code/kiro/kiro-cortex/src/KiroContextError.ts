/**
 * @module KiroContextError
 * Tagged error types for the kiro-cortex service layer.
 *
 * ARCH: All errors extend Schema.TaggedError for Effect's typed error channel.
 * Each service has its own error type so callers can pattern-match on the _tag
 * field to handle errors from different services differently.
 *
 * CONSTRAINT: Every new service or module that can fail should define its own
 * tagged error here. Do NOT use global Error — the Effect language service
 * warns on untagged errors in the failure channel.
 */

import { Schema } from "effect"

/** HTTP API handler errors (used by index.ts endpoint handlers). */
export class TestError extends Schema.TaggedError<TestError>()(
  "TestError",
  { message: Schema.String },
) {}

/** OPA service errors (policy evaluation or scoping failures). */
export class OpaError extends Schema.TaggedError<OpaError>()(
  "OpaError",
  { message: Schema.String },
) {}

/** Embedding service errors (Ollama API failures). */
export class EmbeddingError extends Schema.TaggedError<EmbeddingError>()(
  "EmbeddingError",
  { message: Schema.String },
) {}

/** Instruction repository errors (pgvector search or upsert failures). */
export class InstructionError extends Schema.TaggedError<InstructionError>()(
  "InstructionError",
  { message: Schema.String },
) {}

/** YAML instruction loader errors (file I/O, parsing, or embedding failures). */
export class LoaderError extends Schema.TaggedError<LoaderError>()(
  "LoaderError",
  { message: Schema.String },
) {}
