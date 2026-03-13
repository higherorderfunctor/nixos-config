import { BunContext } from "@effect/platform-bun"
import { PgClient, PgMigrator } from "@effect/sql-pg"
import { Layer } from "effect"
import { fileURLToPath } from "node:url"

const ClientLive = PgClient.layer({ host: "localhost", port: 5435, database: "kiro_cortex" })

const MigratorLive = PgMigrator.layer({
  loader: PgMigrator.fromFileSystem(
    fileURLToPath(new URL("migrations", import.meta.url)),
  ),
  schemaDirectory: "src/migrations",
}).pipe(Layer.provide(BunContext.layer))

export const SqlLive = MigratorLive.pipe(Layer.provideMerge(ClientLive))
