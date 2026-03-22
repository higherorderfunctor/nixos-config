/**
 * @module Opa
 * OPA (Open Policy Agent) typed HTTP client for access control and instruction scoping.
 *
 * ARCH: Uses HttpApi + Schema to define the OPA REST API shape, then derives a
 * fully typed client via HttpApiClient.make(). Schema.transform unwraps OPA's
 * `{ result: T }` envelope at the schema level — callers get domain types directly.
 *
 * ARCH: Uses Context.Tag + Layer.effect (not Effect.Service) because this is a
 * pure HTTP client derived from HttpApiClient.make — no custom logic needed.
 *
 * EXTERNAL: OPA wraps all query results in `{ result: T }` and expects input as
 * `{ input: T }`. Error responses follow `{ code, message, errors? }` shape.
 *
 * EXTERNAL: OPA server expected on localhost:8181.
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
// Error schema — models OPA's documented error response shape
// ---------------------------------------------------------------------------

/** EXTERNAL: OPA error detail with optional source location. */
const OpaErrorDetail = Schema.Struct({
  code: Schema.String,
  message: Schema.String,
  location: Schema.optional(Schema.Struct({
    file: Schema.String,
    row: Schema.Number,
    col: Schema.Number,
  })),
})

/**
 * OPA API error with `_tag` for union discrimination in Effect's error channel.
 *
 * EXTERNAL: OPA returns `{ code, message, errors? }` on 400/500 status codes.
 */
export class OpaApiError extends Schema.TaggedError<OpaApiError>()("OpaApiError", {
  code: Schema.String,
  message: Schema.String,
  errors: Schema.optional(Schema.Array(OpaErrorDetail)),
}) {}

/** EXTERNAL: Transform OPA's raw error JSON (no _tag) → OpaApiError (with _tag). */
const OpaApiErrorFromWire = Schema.transform(
  Schema.Struct({
    code: Schema.String,
    message: Schema.String,
    errors: Schema.optional(Schema.Array(OpaErrorDetail)),
  }),
  Schema.typeSchema(OpaApiError),
  {
    decode: (wire) => new OpaApiError(wire),
    encode: ({ code, message, errors }) => ({ code, message, errors }),
  },
)

// ---------------------------------------------------------------------------
// Success schemas — model OPA responses with envelope unwrapping
// ---------------------------------------------------------------------------

/** OPA access decision — allow/deny with reason. */
export const OpaDecisionSchema = Schema.Struct({
  allowed: Schema.Boolean,
  denied: Schema.Boolean,
  reason: Schema.String,
})

/** OPA scoping filters — translated to SQL WHERE clauses by the block executor. */
export const ScopingFiltersSchema = Schema.Struct({
  allowed_domains: Schema.Array(Schema.String),
  allowed_task_types: Schema.Array(Schema.String),
  repo_filter: Schema.NullOr(Schema.String),
  max_results: Schema.Number,
})

/**
 * EXTERNAL: Schema.transform unwraps OPA's `{ result: OpaDecision }` → `OpaDecision`.
 * The HttpApiClient decodes the wire format and returns the domain type directly.
 */
const OpaAccessSuccess = Schema.transform(
  Schema.Struct({ result: OpaDecisionSchema }),
  OpaDecisionSchema,
  {
    decode: (wire) => wire.result,
    encode: (domain) => ({ result: domain }),
  },
)

/** EXTERNAL: Schema.transform unwraps `{ result: ScopingFilters }` → `ScopingFilters`. */
const OpaScopingSuccess = Schema.transform(
  Schema.Struct({ result: ScopingFiltersSchema }),
  ScopingFiltersSchema,
  {
    decode: (wire) => wire.result,
    encode: (domain) => ({ result: domain }),
  },
)

// ---------------------------------------------------------------------------
// Derived types — exported for use by callers
// ---------------------------------------------------------------------------

/** Input for access control evaluation. */
export type OpaQuery = {
  readonly user_id: string
  readonly query: string
}

/** Result of an OPA access control evaluation. */
export type OpaDecision = typeof OpaDecisionSchema.Type

/** Input for per-block instruction scoping. */
export type ScopingInput = {
  readonly agent_role: string
  readonly task_type: string
  readonly domain: string
  readonly repo: string | null
}

/** Filtering criteria returned by OPA scoping policy. */
export type ScopingFilters = typeof ScopingFiltersSchema.Type

// ---------------------------------------------------------------------------
// HttpApi definition
// ---------------------------------------------------------------------------

// CONSTRAINT: Endpoint paths must match OPA's data API convention:
// /v1/data/{package_path}/{rule_name}

const OpaQueryInput = Schema.Struct({
  input: Schema.Struct({
    user_id: Schema.String,
    query: Schema.String,
  }),
})

const ScopingPayload = Schema.Struct({
  input: Schema.Struct({
    agent_role: Schema.String,
    task_type: Schema.String,
    domain: Schema.String,
    repo: Schema.NullOr(Schema.String),
  }),
})

const AccessEndpoint = HttpApiEndpoint.post("evaluate")`/v1/data/cortex/access/decision`
  .setPayload(OpaQueryInput)
  .addSuccess(OpaAccessSuccess)
  .addError(OpaApiErrorFromWire, { status: 400 })
  .addError(OpaApiErrorFromWire, { status: 500 })

const ScopingEndpoint = HttpApiEndpoint.post("scope")`/v1/data/cortex/scoping/filters`
  .setPayload(ScopingPayload)
  .addSuccess(OpaScopingSuccess)
  .addError(OpaApiErrorFromWire, { status: 400 })
  .addError(OpaApiErrorFromWire, { status: 500 })

class OpaGroup extends HttpApiGroup.make("opa")
  .add(AccessEndpoint)
  .add(ScopingEndpoint)
{}

class OpaApi extends HttpApi.make("opaApi").add(OpaGroup) {}

// ---------------------------------------------------------------------------
// Context.Tag + Layer — typed OPA client
// ---------------------------------------------------------------------------

/**
 * ARCH: HttpApiClient.make derives a fully typed client from the API definition.
 * Schema.transform handles envelope unwrapping, .addError() handles error typing.
 */
const make = HttpApiClient.make(OpaApi, {
  baseUrl: "http://localhost:8181",
})

/**
 * OPA client tag for dependency injection.
 *
 * ARCH: Uses Context.Tag + Layer.effect (not Effect.Service) because this is a
 * pure HTTP client derived from HttpApiClient.make — no custom logic needed.
 */
export class OpaClient extends Context.Tag("OpaClient")<
  OpaClient,
  Effect.Effect.Success<typeof make>
>() {}

/** OPA client layer. Provides OpaClient with NodeHttpClient. */
export const layer = Layer.effect(OpaClient, make).pipe(
  Layer.provide(NodeHttpClient.layer),
)
