import { BunContext } from "@effect/platform-bun"
import { PgClient, PgMigrator } from "@effect/sql-pg"
import { SqlClient } from "@effect/sql"
import { Effect, Layer } from "effect"
import { fileURLToPath } from "node:url"

const pgConfig = { host: "localhost", port: 5435 } as const

const bootstrapDb = Effect.gen(function* () {
  yield* Effect.log("Bootstrapping database...")
  const sql = yield* SqlClient.SqlClient
  yield* sql.unsafe(`CREATE DATABASE kiro_cortex`).pipe(
    Effect.tap(() => Effect.log("Created database kiro_cortex")),
    Effect.catchAll(() => Effect.log("Database kiro_cortex already exists")),
  )
}).pipe(Effect.provide(PgClient.layer({ ...pgConfig, database: "postgres" })))

const ClientLive = PgClient.layer({ ...pgConfig, database: "kiro_cortex" })

const MigratorLive = PgMigrator.layer({
  loader: PgMigrator.fromFileSystem(
    fileURLToPath(new URL("migrations", import.meta.url)),
  ),
  schemaDirectory: "src/migrations",
}).pipe(Layer.provide(BunContext.layer))

export const SqlLive = Layer.unwrapEffect(
  bootstrapDb.pipe(
    Effect.map(() => MigratorLive.pipe(Layer.provideMerge(ClientLive))),
  ),
).pipe(Layer.tap(() => Effect.log("Database ready (migrations applied)")))
