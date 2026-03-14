import { Effect, Option } from "effect"
import type { BlockDef } from "./Block.js"

export class BlockRegistry extends Effect.Service<BlockRegistry>()("BlockRegistry", {
  effect: Effect.sync(() => {
    const blocks = new Map<string, BlockDef<any>>()

    const register = (block: BlockDef<any>): void => {
      blocks.set(block.id, block)
    }

    const get = (id: string): Option.Option<BlockDef<any>> =>
      Option.fromNullable(blocks.get(id))

    const list = (): ReadonlyArray<BlockDef<any>> =>
      Array.from(blocks.values())

    const search = (query: string): ReadonlyArray<BlockDef<any>> => {
      const q = query.toLowerCase()
      return Array.from(blocks.values()).filter((b) =>
        b.name.toLowerCase().includes(q)
        || b.description.toLowerCase().includes(q)
        || b.tags.some((t) => t.toLowerCase().includes(q)),
      )
    }

    return { register, get, list, search } as const
  }),
}) {}
