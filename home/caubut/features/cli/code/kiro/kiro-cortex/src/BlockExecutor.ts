/**
 * @module BlockExecutor
 * Generic block execution engine — the core of "scale to millions."
 *
 * ARCH: Each block declares its OPA context (agent_role, task_type, domain).
 * The executor queries OPA for scoping filters, searches pgvector with those
 * filters, and injects the retrieved instructions into state as `_context`.
 * This means each block only sees its OPA-scoped slice of instructions.
 *
 * ARCH: Uses plain async interface (BlockExecutorServices) instead of Effect
 * services directly. This decouples from the Effect layer system so LangGraph
 * node functions can call it without needing an Effect runtime.
 */

import type { BlockDef } from "./Block.js"
import type { ScopingInput, ScopingFilters } from "./Opa.js"
import type { Instruction, SearchFilters } from "./InstructionRepo.js"

/**
 * Service interface for the block executor. Plain async functions that
 * wrap the underlying Effect services (OPA, Embedding, InstructionRepo).
 *
 * ARCH: Callers construct this by wrapping Effect services with Effect.runPromise.
 * This keeps the executor portable — it doesn't depend on the Effect runtime.
 */
export interface BlockExecutorServices {
  /** Query OPA scoping policy for instruction filtering criteria. */
  readonly scope: (input: ScopingInput) => Promise<ScopingFilters>
  /** Embed text into a vector for pgvector similarity search. */
  readonly embed: (text: string) => Promise<ReadonlyArray<number>>
  /** Search pgvector for instructions matching the embedding and filters. */
  readonly search: (
    embedding: ReadonlyArray<number>,
    filters: SearchFilters,
    limit: number,
  ) => Promise<ReadonlyArray<Instruction>>
}

/**
 * Execute a block with OPA-scoped instruction injection.
 *
 * Flow: OPA scoping → embed block description → pgvector search → inject _context → execute
 *
 * @param block - The block definition to execute.
 * @param state - Current pipeline state.
 * @param services - Async wrappers around OPA, Embedding, and InstructionRepo.
 * @returns Partial state update from the block's execute function.
 */
export const executeBlock = async <S>(
  block: BlockDef<S>,
  state: S,
  services: BlockExecutorServices,
): Promise<Partial<S>> => {
  // --- OPA scoping: determine which instructions this block can see ---
  const filters = await services.scope({ ...block.opa, repo: null })

  // --- Embed block description as the search query ---
  // ARCH: We embed the block's description (not state content) because the
  // description captures the block's PURPOSE, which matches instruction intent.
  const vec = await services.embed(block.description)

  // --- Search pgvector with OPA-derived filters ---
  const instructions = await services.search(
    vec,
    {
      // CONSTRAINT: Use first non-global domain from OPA filters for SQL WHERE
      domain: filters.allowed_domains.find((d) => d !== "global"),
      agent_role: block.opa.agent_role,
      task_type: block.opa.task_type,
    },
    filters.max_results,
  )

  // --- Inject instructions into state and execute ---
  // ARCH: Instructions are injected as `_context` — blocks can read this
  // field to access their scoped instructions. Blocks that don't need
  // instructions simply ignore it (backward compatible).
  const enriched = { ...state, _context: instructions.map((i) => i.text) }
  return block.execute(enriched as S)
}
