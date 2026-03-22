/**
 * @module opa
 * OPA (Open Policy Agent) integration for access control and per-block instruction scoping.
 *
 * Provides a typed HTTP client for OPA's REST API with compile-time and runtime
 * validation via HttpApi + Schema. Schema.transform unwraps OPA's `{ result: T }`
 * envelope — callers get domain types directly. Handles two query types:
 *
 * - Access control: allow/deny decisions with reason (used by index.ts /context endpoint)
 * - Instruction scoping: per-block filtering criteria for pgvector search (used by workflow/Executor)
 *
 * Public API:
 * - {@link OpaClient} — Context.Tag for the HttpApi-derived client
 * - {@link layer} — Layer providing OpaClient with NodeHttpClient
 * - {@link OpaApiError} — TaggedError for OPA error responses
 * - {@link OpaDecisionSchema} / {@link ScopingFiltersSchema} — response schemas
 * - Type exports for OPA query/response shapes
 *
 * EXTERNAL: OPA server expected on localhost:8181
 */

export { OpaClient, OpaApiError, OpaDecisionSchema, ScopingFiltersSchema, layer } from "./Opa.js"
export type { OpaQuery, OpaDecision, ScopingInput, ScopingFilters } from "./Opa.js"
