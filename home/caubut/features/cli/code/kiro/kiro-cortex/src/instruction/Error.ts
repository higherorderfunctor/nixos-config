/**
 * @module instruction/Error
 * Tagged error types for the instruction domain.
 */

import { Schema } from "effect"

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
