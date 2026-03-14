/**
 * @module Opa
 * OPA (Open Policy Agent) service for access control and per-block instruction scoping.
 *
 * ARCH: Uses HttpApi + Schema to define the OPA REST API shape, then derives a
 * fully typed client via HttpApiClient.make(). This eliminates `as any` casts and
 * gives compile-time + runtime validation on both request and response bodies.
 *
 * EXTERNAL: OPA wraps all query results in `{ result: T }`. Our response schemas
 * model this wrapper honestly — the service methods unwrap `.result` for callers.
 *
 * EXTERNAL: OPA expects input as `{ input: T }` in the request body. Our payload
 * schemas model this wrapper so the client sends the correct shape.
 */

import { Effect, Schema } from "effect"
import {
  HttpApi,
  HttpApiClient,
  HttpApiEndpoint,
  HttpApiGroup,
} from "@effect/platform"
import { NodeHttpClient } from "@effect/platform-node"
import { OpaError } from "../KiroContextError.js"

// ---------------------------------------------------------------------------
// Schemas — model the real OPA API shapes honestly
// ---------------------------------------------------------------------------

/** Access control query sent to OPA. Wrapped in `{ input: ... }` per OPA convention. */
const OpaQueryInput = Schema.Struct({
  input: Schema.Struct({
    user_id: Schema.String,
    query: Schema.String,
  }),
})

/** OPA access decision — allow/deny with reason. */
export const OpaDecisionSchema = Schema.Struct({
  allowed: Schema.Boolean,
  denied: Schema.Boolean,
  reason: Schema.String,
})

/** OPA wraps results: `{ result: OpaDecision }`. */
const OpaAccessResponse = Schema.Struct({
  result: OpaDecisionSchema,
})

/** Per-block scoping query sent to OPA. Determines which instructions a block can see. */
const ScopingPayload = Schema.Struct({
  input: Schema.Struct({
    agent_role: Schema.String,
    task_type: Schema.String,
    domain: Schema.String,
    repo: Schema.NullOr(Schema.String),
  }),
})

/** OPA scoping filters — translated to SQL WHERE clauses by the block executor. */
export const ScopingFiltersSchema = Schema.Struct({
  allowed_domains: Schema.Array(Schema.String),
  allowed_task_types: Schema.Array(Schema.String),
  repo_filter: Schema.NullOr(Schema.String),
  max_results: Schema.Number,
})

/** OPA wraps results: `{ result: ScopingFilters }`. */
const OpaScopingResponse = Schema.Struct({
  result: ScopingFiltersSchema,
})

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
// HttpApi definition — describes the OPA REST API shape for client derivation
// ---------------------------------------------------------------------------

// CONSTRAINT: Endpoint paths must match OPA's data API convention:
// /v1/data/{package_path}/{rule_name}

const AccessEndpoint = HttpApiEndpoint.post("evaluate")`/v1/data/cortex/access/decision`
  .setPayload(OpaQueryInput)
  .addSuccess(OpaAccessResponse)

const ScopingEndpoint = HttpApiEndpoint.post("scope")`/v1/data/cortex/scoping/filters`
  .setPayload(ScopingPayload)
  .addSuccess(OpaScopingResponse)

class OpaGroup extends HttpApiGroup.make("opa")
  .add(AccessEndpoint)
  .add(ScopingEndpoint)
{}

class OpaApi extends HttpApi.make("opaApi").add(OpaGroup) {}

// ---------------------------------------------------------------------------
// Service — typed OPA client with unwrapped results
// ---------------------------------------------------------------------------

/**
 * OPA service providing access control and per-block instruction scoping.
 *
 * ARCH: Implemented as an Effect.Service so it can be provided via Layer
 * composition. The HttpApi client is created once during service construction
 * and reused for all queries.
 */
export class OpaService extends Effect.Service<OpaService>()("OpaService", {
  dependencies: [NodeHttpClient.layer],
  effect: Effect.gen(function* () {
    // ARCH: HttpApiClient.make derives a fully typed client from the API definition.
    // All request payloads are Schema-encoded, all responses are Schema-validated.
    const client = yield* HttpApiClient.make(OpaApi, {
      baseUrl: "http://localhost:8181",
    })

    /**
     * Evaluate an access control query against OPA.
     * @returns The access decision (allowed/denied/reason), unwrapped from OPA's result envelope.
     */
    const evaluate = (query: OpaQuery): Effect.Effect<OpaDecision, OpaError> =>
      client.opa.evaluate({ payload: { input: query } }).pipe(
        // EXTERNAL: OPA wraps in { result: ... }, unwrap for callers
        Effect.map((response) => response.result),
        Effect.mapError((error) => new OpaError({ message: String(error) })),
      )

    /**
     * Query OPA for per-block instruction scoping filters.
     * @returns Filtering criteria (allowed_domains, allowed_task_types, repo_filter, max_results).
     */
    const scope = (input: ScopingInput): Effect.Effect<ScopingFilters, OpaError> =>
      client.opa.scope({ payload: { input } }).pipe(
        // EXTERNAL: OPA wraps in { result: ... }, unwrap for callers
        Effect.map((response) => response.result),
        Effect.mapError((error) => new OpaError({ message: String(error) })),
      )

    return { evaluate, scope } as const
  }),
}) {}
