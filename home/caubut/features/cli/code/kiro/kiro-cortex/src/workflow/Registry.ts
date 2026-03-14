/**
 * @module BlockRegistry
 * In-memory registry for block definitions. Supports lookup by ID, listing, and search.
 *
 * ARCH: Implemented as an Effect.Service (infrastructure, not domain logic).
 * Blocks register themselves at startup. The registry uses `any` for the state
 * type parameter because it holds blocks from multiple pipelines with different
 * state shapes — this is the one place where generic erasure is unavoidable.
 */

import { Effect, Option } from "effect"
import type { BlockDef } from "./Block.js"

/**
 * In-memory block registry. Holds all registered block definitions for
 * discovery by the pipeline executor and MCP tools.
 */
export class BlockRegistry extends Effect.Service<BlockRegistry>()("BlockRegistry", {
  effect: Effect.sync(() => {
    // CONSTRAINT: Map uses `any` for state type — blocks from different pipelines
    // have different state shapes. Type safety is enforced at the pipeline level.
    const blocks = new Map<string, BlockDef<any>>()

    /** Register a block definition. Overwrites if ID already exists. */
    const register = (block: BlockDef<any>): void => {
      blocks.set(block.id, block)
    }

    /** Look up a block by ID. Returns Option.none if not found. */
    const get = (id: string): Option.Option<BlockDef<any>> =>
      Option.fromNullable(blocks.get(id))

    /** List all registered blocks. */
    const list = (): ReadonlyArray<BlockDef<any>> =>
      Array.from(blocks.values())

    /** Search blocks by name, description, or tags (case-insensitive substring match). */
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

/** BlockRegistry layer alias for consistent `export const layer` convention. */
export const layer = BlockRegistry.Default
