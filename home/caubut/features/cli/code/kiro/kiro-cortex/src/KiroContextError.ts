import { Schema } from "effect"

export class TestError extends Schema.TaggedError<TestError>()(
  "TestError",
  { message: Schema.String },
) {}

export class OpaError extends Schema.TaggedError<OpaError>()(
  "OpaError",
  { message: Schema.String },
) {}

export class EmbeddingError extends Schema.TaggedError<EmbeddingError>()(
  "EmbeddingError",
  { message: Schema.String },
) {}

export class InstructionError extends Schema.TaggedError<InstructionError>()(
  "InstructionError",
  { message: Schema.String },
) {}

export class LoaderError extends Schema.TaggedError<LoaderError>()(
  "LoaderError",
  { message: Schema.String },
) {}
