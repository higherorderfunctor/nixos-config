/**
 * @module Sql
 * PostgreSQL connection and migration layer.
 *
 * ARCH: Uses @effect/sql-pg for connection pooling and @effect/sql-pg PgMigrator
 * for schema migrations. Migrations are loaded from the filesystem (src/migrations/).
 * The migrator runs automatically when the layer is built — no manual migration step.
 *
 * CONSTRAINT: Database runs on port 5435 (non-standard) to avoid conflicts with
 * system PostgreSQL. Managed by NixOS/Home Manager.
 */

import { BunContext } from "@effect/platform-bun"
import { PgClient, PgMigrator } from "@effect/sql-pg"
import { Layer } from "effect"
import { fileURLToPath } from "node:url"

/** PostgreSQL connection pool — connects to kiro_cortex database on localhost:5435. */
const ClientLive = PgClient.layer({ host: "localhost", port: 5435, database: "kiro_cortex" })

/**
 * Schema migrator — reads migration files from src/migrations/ and applies them
 * in order. Runs automatically during layer construction.
 */
const MigratorLive = PgMigrator.layer({
  loader: PgMigrator.fromFileSystem(
    fileURLToPath(new URL("migrations", import.meta.url)),
  ),
  schemaDirectory: "src/migrations",
}).pipe(Layer.provide(BunContext.layer))

/**
 * Combined SQL layer: connection pool + auto-migration.
 * Provides SqlClient to all downstream services (InstructionRepo, etc.).
 */
export const SqlLive = MigratorLive.pipe(Layer.provideMerge(ClientLive))
