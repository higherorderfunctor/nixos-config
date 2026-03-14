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

    return { search } as const
  }),
}) {}
