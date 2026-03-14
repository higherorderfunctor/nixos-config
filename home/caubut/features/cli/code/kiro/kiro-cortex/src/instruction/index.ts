/**
 * @module instruction
 * Instruction storage, retrieval, and startup loading.
 *
 * Instructions are the core data model — text with OPA metadata stored in
 * PostgreSQL/pgvector. This domain handles:
 *
 * - Storage and similarity search via pgvector HNSW index ({@link InstructionRepo})
 * - Startup loading from YAML files with content-hash idempotency ({@link loadInstructions})
 *
 * Public API:
 * - {@link InstructionRepo} — Effect.Service for pgvector CRUD and search
 * - {@link layer} — InstructionRepo layer alias
 * - {@link loadInstructions} — startup Effect that reads YAML and upserts
 * - {@link InstructionError} / {@link LoaderError} — domain error types
 * - Type exports for instruction shapes and search filters
 *
 * Used by: workflow/Executor (search at block execution), index.ts (startup load)
 * Depends on: embedding (vector generation), Sql (PostgreSQL connection)
 */

export { InstructionRepo, layer } from "./Repo.js"
export type { Instruction, SearchFilters, UpsertInput } from "./Repo.js"
export { loadInstructions } from "./Loader.js"
export { InstructionError, LoaderError } from "./Error.js"
