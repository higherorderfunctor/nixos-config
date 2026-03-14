import { Effect } from "effect"
import { readdir, readFile } from "node:fs/promises"
import { join } from "node:path"
import { createHash } from "node:crypto"
import { parse } from "yaml"
import { EmbeddingService } from "./Embedding.js"
import { InstructionRepo, type UpsertInput } from "./InstructionRepo.js"
import { LoaderError } from "./KiroContextError.js"

const md5 = (text: string) => createHash("md5").update(text).digest("hex")

const toUuid = (input: string): string => {
  const h = md5(input)
  return `${h.slice(0, 8)}-${h.slice(8, 12)}-${h.slice(12, 16)}-${h.slice(16, 20)}-${h.slice(20, 32)}`
}

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

const findYamlFiles = (workflowsDir: string) =>
  Effect.tryPromise({
    try: async () => {
      const workflows = await readdir(workflowsDir, { withFileTypes: true })
      const files: Array<string> = []
      for (const wf of workflows) {
        if (!wf.isDirectory()) continue
        const instrDir = join(workflowsDir, wf.name, "instructions")
        try {
          const entries = await readdir(instrDir)
          for (const f of entries) {
            if (f.endsWith(".yaml")) files.push(join(instrDir, f))
          }
        } catch { /* no instructions dir — skip */ }
      }
      return files
    },
    catch: (e) => new LoaderError({ message: `Failed to scan workflows: ${e}` }),
  })

const parseYaml = (path: string) =>
  Effect.tryPromise({
    try: async () => parse(await readFile(path, "utf-8")) as YamlInstruction,
    catch: (e) => new LoaderError({ message: `Failed to parse ${path}: ${e}` }),
  })

export const loadInstructions = Effect.gen(function* () {
  const embedding = yield* EmbeddingService
  const repo = yield* InstructionRepo

  const workflowsDir = join(import.meta.dir, "..", "workflows")
  const files = yield* findYamlFiles(workflowsDir)

  let loaded = 0
  for (const file of files) {
    const doc = yield* parseYaml(file)
    const contentHash = md5(doc.text)
    const id = toUuid(doc.id)
    const vec = yield* embedding.embed(doc.text).pipe(
      Effect.mapError((e) => new LoaderError({ message: e.message })),
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

  yield* Effect.log(`Loaded ${loaded} instructions from ${files.length} YAML files`)
})
