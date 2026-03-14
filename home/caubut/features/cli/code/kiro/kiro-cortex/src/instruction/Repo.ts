/**
 * @module InstructionRepo
 * PostgreSQL + pgvector repository for instruction storage and similarity search.
 *
 * ARCH: Instructions are the core data model — text with OPA metadata that gets
 * injected into block execution context. This service handles both search (cosine
 * similarity via pgvector HNSW index) and upsert (idempotent via content_hash).
 *
 * CONSTRAINT: Vector dimension is 768 (nomic-embed-text). Changing the embedding
 * model requires re-embedding all instructions.
 */

import { Effect } from "effect"
import { SqlClient } from "@effect/sql"
import { InstructionError } from "../KiroContextError.js"

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

/** A single instruction retrieved from pgvector search, with distance score. */
export interface Instruction {
  readonly id: string
  readonly text: string
  readonly source: string | null
  readonly domain: string | null
  readonly subdomain: string | null
  readonly repo: string | null
  readonly priority: string | null
  /** Cosine distance from the query vector (lower = more similar). */
  readonly distance: number
}

/** Filters for narrowing instruction search. All fields optional — omitted = no filter. */
export interface SearchFilters {
  readonly domain?: string | undefined
  readonly agent_role?: string | undefined
  readonly task_type?: string | undefined
  readonly tier?: number | undefined
}

/** Input for upserting an instruction into pgvector. */
export interface UpsertInput {
  /** Deterministic UUID derived from the instruction's string ID. */
  readonly id: string
  /** The instruction text that gets injected into block context. */
  readonly text: string
  /** 768-dimensional embedding vector from nomic-embed-text. */
  readonly embedding: ReadonlyArray<number>
  readonly domain: string | null
  /** OPA agent roles that can see this instruction. */
  readonly agent_roles: ReadonlyArray<string>
  /** OPA task types this instruction applies to. */
  readonly task_types: ReadonlyArray<string>
  readonly repo: string | null
  /** MD5 of text — used for change detection (skip upsert if unchanged). */
  readonly content_hash: string
  /** Filesystem path to the source YAML file. */
  readonly source: string
}

// ---------------------------------------------------------------------------
// Service
// ---------------------------------------------------------------------------

/**
 * Instruction repository backed by PostgreSQL + pgvector.
 * Provides cosine similarity search and idempotent upsert.
 */
export class InstructionRepo extends Effect.Service<InstructionRepo>()("InstructionRepo", {
  dependencies: [],
  effect: Effect.gen(function* () {
    const sql = yield* SqlClient.SqlClient

    /**
     * Search instructions by vector similarity with optional metadata filters.
     * Uses pgvector's HNSW index for fast approximate nearest neighbor search.
     *
     * @param embedding - Query vector (768-dim).
     * @param filters - Optional metadata filters (domain, agent_role, task_type, tier).
     * @param limit - Maximum number of results.
     * @returns Instructions ordered by cosine distance (ascending = most similar first).
     */
    const search = (
      embedding: ReadonlyArray<number>,
      filters: SearchFilters,
      limit: number,
    ): Effect.Effect<ReadonlyArray<Instruction>, InstructionError> =>
      Effect.gen(function* () {
        const vecStr = `[${embedding.join(",")}]`

        // --- Build dynamic WHERE clause from filters ---
        const conditions = [sql`1=1`] as Array<any>
        if (filters.domain) conditions.push(sql`domain = ${filters.domain}`)
        if (filters.agent_role) conditions.push(sql`${filters.agent_role} = ANY(agent_roles)`)
        if (filters.task_type) conditions.push(sql`${filters.task_type} = ANY(task_types)`)
        if (filters.tier) conditions.push(sql`${filters.tier} = ANY(tier_access)`)

        // EXTERNAL: pgvector uses <=> operator for cosine distance
        const rows = yield* sql<Instruction>`
          SELECT id, text, source, domain, subdomain, repo, priority,
                 embedding <=> ${sql.unsafe(`'${vecStr}'`)}::vector AS distance
          FROM instructions
          WHERE ${sql.and(conditions)}
            AND (expiry_date IS NULL OR expiry_date > NOW())
          ORDER BY embedding <=> ${sql.unsafe(`'${vecStr}'`)}::vector
          LIMIT ${limit}
        `
        return rows
      }).pipe(
        Effect.mapError((e) => new InstructionError({ message: String(e) })),
      )

    /**
     * Upsert an instruction into pgvector. Idempotent via content_hash —
     * only updates if the text has actually changed.
     *
     * ARCH: Uses ON CONFLICT (id) DO UPDATE with a WHERE clause that checks
     * content_hash. If the hash matches, the row is untouched (no unnecessary
     * writes, no updated_at churn).
     */
    const upsert = (input: UpsertInput): Effect.Effect<void, InstructionError> =>
      Effect.gen(function* () {
        const vecStr = `[${input.embedding.join(",")}]`
        // EXTERNAL: PostgreSQL array literal format for TEXT[] columns
        const roles = `{${input.agent_roles.join(",")}}`
        const types = `{${input.task_types.join(",")}}`

        yield* sql`
          INSERT INTO instructions (id, text, embedding, domain, agent_roles, task_types, repo, content_hash, source, updated_at)
          VALUES (
            ${input.id}::uuid,
            ${input.text},
            ${sql.unsafe(`'${vecStr}'`)}::vector,
            ${input.domain},
            ${roles}::text[],
            ${types}::text[],
            ${input.repo},
            ${input.content_hash},
            ${input.source},
            NOW()
          )
          ON CONFLICT (id) DO UPDATE SET
            text = EXCLUDED.text,
            embedding = EXCLUDED.embedding,
            domain = EXCLUDED.domain,
            agent_roles = EXCLUDED.agent_roles,
            task_types = EXCLUDED.task_types,
            repo = EXCLUDED.repo,
            content_hash = EXCLUDED.content_hash,
            source = EXCLUDED.source,
            updated_at = NOW()
          WHERE instructions.content_hash IS DISTINCT FROM EXCLUDED.content_hash
        `
      }).pipe(
        Effect.asVoid,
        Effect.mapError((e) => new InstructionError({ message: String(e) })),
      )

    return { search, upsert } as const
  }),
}) {}
