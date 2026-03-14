import { Effect } from "effect"
import { SqlClient } from "@effect/sql"
import { InstructionError } from "./KiroContextError.js"

export interface Instruction {
  readonly id: string
  readonly text: string
  readonly source: string | null
  readonly domain: string | null
  readonly subdomain: string | null
  readonly repo: string | null
  readonly priority: string | null
  readonly distance: number
}

export interface SearchFilters {
  readonly domain?: string | undefined
  readonly agent_role?: string | undefined
  readonly task_type?: string | undefined
  readonly tier?: number | undefined
}

export interface UpsertInput {
  readonly id: string
  readonly text: string
  readonly embedding: ReadonlyArray<number>
  readonly domain: string | null
  readonly agent_roles: ReadonlyArray<string>
  readonly task_types: ReadonlyArray<string>
  readonly repo: string | null
  readonly content_hash: string
  readonly source: string
}

export class InstructionRepo extends Effect.Service<InstructionRepo>()("InstructionRepo", {
  dependencies: [],
  effect: Effect.gen(function* () {
    const sql = yield* SqlClient.SqlClient

    const search = (
      embedding: ReadonlyArray<number>,
      filters: SearchFilters,
      limit: number,
    ): Effect.Effect<ReadonlyArray<Instruction>, InstructionError> =>
      Effect.gen(function* () {
        const vecStr = `[${embedding.join(",")}]`
        const conditions = [sql`1=1`] as Array<any>

        if (filters.domain) conditions.push(sql`domain = ${filters.domain}`)
        if (filters.agent_role) conditions.push(sql`${filters.agent_role} = ANY(agent_roles)`)
        if (filters.task_type) conditions.push(sql`${filters.task_type} = ANY(task_types)`)
        if (filters.tier) conditions.push(sql`${filters.tier} = ANY(tier_access)`)

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

    const upsert = (input: UpsertInput): Effect.Effect<void, InstructionError> =>
      Effect.gen(function* () {
        const vecStr = `[${input.embedding.join(",")}]`
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
