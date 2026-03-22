import { Effect } from "effect"
import { SqlClient } from "@effect/sql"

export default Effect.gen(function* () {
  const sql = yield* SqlClient.SqlClient

  yield* sql`ALTER TABLE instructions ADD COLUMN IF NOT EXISTS source VARCHAR(255)`
  yield* sql`ALTER TABLE instructions ADD COLUMN IF NOT EXISTS repo VARCHAR(255)`
  yield* sql`ALTER TABLE instructions ADD COLUMN IF NOT EXISTS effective_date TIMESTAMP`
  yield* sql`ALTER TABLE instructions ADD COLUMN IF NOT EXISTS expiry_date TIMESTAMP`
})
