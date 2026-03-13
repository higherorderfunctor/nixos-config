import { Effect } from "effect"
import { SqlClient } from "@effect/sql"

export default Effect.gen(function* () {
  const sql = yield* SqlClient.SqlClient

  yield* sql`CREATE EXTENSION IF NOT EXISTS vector`

  yield* sql`
    CREATE TABLE instructions (
      id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
      text TEXT NOT NULL,
      domain VARCHAR(100),
      subdomain VARCHAR(100),
      tier_access INTEGER[],
      agent_roles TEXT[],
      task_types TEXT[],
      priority VARCHAR(20),
      version VARCHAR(20),
      dependencies UUID[],
      conflict_group VARCHAR(100),
      embedding vector(768),
      created_at TIMESTAMP DEFAULT NOW(),
      updated_at TIMESTAMP DEFAULT NOW()
    )
  `

  yield* sql`CREATE INDEX ON instructions USING hnsw (embedding vector_cosine_ops)`
  yield* sql`CREATE INDEX ON instructions (domain, subdomain)`
  yield* sql`CREATE INDEX ON instructions USING GIN (agent_roles)`
  yield* sql`CREATE INDEX ON instructions USING GIN (task_types)`
})
