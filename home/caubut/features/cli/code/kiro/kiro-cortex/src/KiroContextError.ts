import { Schema } from "effect"

export class TestError extends Schema.TaggedError<TestError>()(
  "TestError",
  { message: Schema.String },
) {}

export class OpaError extends Schema.TaggedError<OpaError>()(
  "OpaError",
  { message: Schema.String },
) {}
