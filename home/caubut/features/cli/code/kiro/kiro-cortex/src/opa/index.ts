/**
 * @module opa
 * OPA (Open Policy Agent) integration for access control and per-block instruction scoping.
 *
 * Provides a typed HTTP client for OPA's REST API with compile-time and runtime
 * validation via HttpApi + Schema. Handles two query types:
 *
 * - Access control: allow/deny decisions with reason (used by index.ts /context endpoint)
 * - Instruction scoping: per-block filtering criteria for pgvector search (used by workflow/Executor)
 *
 * Public API:
 * - {@link OpaService} — Effect.Service wrapping the HttpApi client
 * - {@link OpaDecisionSchema} / {@link ScopingFiltersSchema} — response schemas
 * - Type exports for OPA query/response shapes
 *
 * EXTERNAL: OPA server expected on localhost:8181
 */

export { OpaService, OpaDecisionSchema, ScopingFiltersSchema } from "./Opa.js"
export type { OpaQuery, OpaDecision, ScopingInput, ScopingFilters } from "./Opa.js"
