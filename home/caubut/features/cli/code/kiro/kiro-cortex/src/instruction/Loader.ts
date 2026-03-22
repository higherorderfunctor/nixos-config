/**
 * @module InstructionLoader
 * Startup loader that reads YAML instruction files and upserts them into pgvector.
 *
 * ARCH: Runs once at server startup before the HTTP server begins accepting requests.
 * Reads all instruction YAML files from workflow directories, embeds text via Ollama, and
 * upserts into PostgreSQL with content_hash idempotency (unchanged instructions are skipped).
 *
 * ARCH: Vectors are NOT stored in YAML — they're re-embedded at load time. This ensures
 * consistency when the embedding model changes (just re-run the loader).
 *
 * CONSTRAINT: Deterministic UUIDs are generated from instruction string IDs via MD5.
 * This means the same instruction ID always maps to the same DB row, enabling upsert.
 */

import { Effect } from "effect"
import { readdir, readFile } from "node:fs/promises"
import { join } from "node:path"
import { createHash } from "node:crypto"
import { parse } from "yaml"
import { embed as embedText } from "../embedding/index.js"
import { InstructionRepo, type UpsertInput } from "./Repo.js"
import { LoaderError } from "./Error.js"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/** Compute MD5 hash of a string (used for content_hash and deterministic UUIDs). */
const md5 = (text: string) => createHash("md5").update(text).digest("hex")

/**
 * Generate a deterministic UUID from a string identifier.
 * ARCH: MD5 hash formatted as UUID — same input always produces same UUID.
 * This gives stable DB primary keys for YAML-defined instructions.
 */
const toUuid = (input: string): string => {
  const h = md5(input)
  return `${h.slice(0, 8)}-${h.slice(8, 12)}-${h.slice(12, 16)}-${h.slice(16, 20)}-${h.slice(20, 32)}`
}

// ---------------------------------------------------------------------------
// YAML shape — matches the instruction YAML files on disk
// ---------------------------------------------------------------------------

/** Shape of a YAML instruction file — single instruction or array (UC-MW-30). */
interface YamlInstruction {
  readonly id: string
  readonly text: string
  readonly metadata: {
    readonly agent_role: string
    readonly task_type: string
    readonly domain: string
    readonly repo: string | null
  }
}

/** Multi-instruction YAML: array wrapper (UC-MW-30). */
interface YamlInstructionArray {
  readonly instructions: ReadonlyArray<YamlInstruction>
}

/** Normalize single, array, or wrapped YAML into instruction array. */
const normalizeYaml = (doc: unknown): ReadonlyArray<YamlInstruction> => {
  if (doc && typeof doc === "object" && "instructions" in doc && Array.isArray((doc as YamlInstructionArray).instructions))
    return (doc as YamlInstructionArray).instructions
  if (Array.isArray(doc)) return doc as ReadonlyArray<YamlInstruction>
  return [doc as YamlInstruction]
}

// ---------------------------------------------------------------------------
// File discovery
// ---------------------------------------------------------------------------

/**
 * Recursively find all .yaml files under a directory.
 * Supports hierarchical layout: instructions/<domain>/<topic>.yaml (UC-MW-31).
 */
const walkYaml = async (dir: string, files: Array<string>): Promise<void> => {
  const entries = await readdir(dir, { withFileTypes: true })
  for (const e of entries) {
    const full = join(dir, e.name)
    if (e.isDirectory()) await walkYaml(full, files)
    else if (e.name.endsWith(".yaml")) files.push(full)
  }
}

/**
 * Find all instruction YAML files under the agents directory.
 * Scans each agent's instructions subdirectory recursively for .yaml files.
 */
const findYamlFiles = (agentsDir: string) =>
  Effect.tryPromise({
    try: async () => {
      const agents = await readdir(agentsDir, { withFileTypes: true })
      const files: Array<string> = []
      for (const agent of agents) {
        if (!agent.isDirectory()) continue
        const instrDir = join(agentsDir, agent.name, "instructions")
        try { await walkYaml(instrDir, files) } catch { /* no instructions dir — skip */ }
      }
      return files
    },
    catch: (e) => new LoaderError({ message: `Failed to scan agents: ${e}` }),
  })

/** Parse a YAML file into a raw object (normalized by caller). */
const parseYaml = (path: string) =>
  Effect.tryPromise({
    try: async () => parse(await readFile(path, "utf-8")) as unknown,
    catch: (e) => new LoaderError({ message: `Failed to parse ${path}: ${e}` }),
  })

// ---------------------------------------------------------------------------
// Main loader
// ---------------------------------------------------------------------------

/**
 * Load all instruction YAML files into pgvector.
 *
 * For each YAML file:
 * 1. Parse YAML → typed instruction
 * 2. Compute MD5 content_hash of text
 * 3. Generate deterministic UUID from instruction ID
 * 4. Embed text via Ollama (nomic-embed-text, 768-dim)
 * 5. Upsert into pgvector (skips if content_hash unchanged)
 *
 * ARCH: Requires EmbeddingClient and InstructionRepo in the Effect context.
 * Called from index.ts before server launch.
 */
export const loadInstructions = Effect.gen(function* () {
  const repo = yield* InstructionRepo

  const agentsDir = join(import.meta.dir, "..", "..", "agents")
  const files = yield* findYamlFiles(agentsDir)

  let loaded = 0
  for (const file of files) {
    const raw = yield* parseYaml(file)
    const docs = normalizeYaml(raw)

    for (const doc of docs) {
      const contentHash = md5(doc.text)
      const id = toUuid(doc.id)

      const vec = yield* embedText(doc.text).pipe(
        Effect.mapError((e) => new LoaderError({ message: String(e) })),
      )

      const input: UpsertInput = {
        id,
        text: doc.text,
        embedding: vec,
        domain: doc.metadata.domain,
        agent_roles: [doc.metadata.agent_role],
        task_types: [doc.metadata.task_type],
        repo: doc.metadata.repo,
        content_hash: contentHash,
        source: file,
      }

      yield* repo.upsert(input).pipe(
        Effect.mapError((e) => new LoaderError({ message: e.message })),
      )
      loaded++
    }
  }

  yield* Effect.log(`Loaded ${loaded} instructions from ${files.length} YAML files`)
})
