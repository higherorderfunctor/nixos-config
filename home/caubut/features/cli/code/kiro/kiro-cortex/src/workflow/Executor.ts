/**
 * @module BlockExecutor
 * Generic block execution engine — the core of "scale to millions."
 *
 * ARCH: Each block declares its OPA context (agent_role, task_type, domain).
 * The executor queries OPA for scoping filters, searches pgvector with those
 * filters, and injects the retrieved instructions into state as `_context`.
 * This means each block only sees its OPA-scoped slice of instructions.
 *
 * ARCH (5.6): Adaptive retrieval with distance-based sizing. OPA max_results
 * is a ceiling (safety cap), not a target. Cosine distance cutoff stops
 * returning irrelevant results. Blocks get exactly as many relevant
 * instructions as exist — no fixed result count.
 *
 * ARCH: Uses plain async interface (BlockExecutorServices) instead of Effect
 * services directly. This decouples from the Effect layer system so LangGraph
 * node functions can call it without needing an Effect runtime.
 */

import type { BlockDef } from "./Block.js"
import type { ScopingInput, ScopingFilters } from "../opa/index.js"
import type { Instruction, SearchFilters } from "../instruction/index.js"

/**
 * Cosine distance cutoff — instructions above this distance are irrelevant.
 * Lower = stricter (fewer results). pgvector cosine distance range: 0 (identical) to 2 (opposite).
 * 0.5 is a reasonable default for nomic-embed-text; tune after 5.7 load test.
 */
const COSINE_DISTANCE_CUTOFF = 0.5

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

/** Metadata from instruction retrieval, injected as `_context_meta` on state. */
export interface ContextMeta {
  /** Block hit the OPA ceiling — may have missed relevant instructions. */
  readonly ceiling_hit: boolean
  /** Number of instructions returned (after distance cutoff). */
  readonly count: number
  /** Number of instructions dropped by distance cutoff. */
  readonly dropped: number
}

/**
 * Execute a block with OPA-scoped instruction injection.
 *
 * Flow: OPA scoping → embed block description → pgvector search → distance cutoff → inject _context → execute
 *
 * ARCH (5.6): Two-phase filtering:
 * 1. pgvector returns up to max_results (OPA ceiling) ordered by distance
 * 2. Executor filters by COSINE_DISTANCE_CUTOFF — drops irrelevant tail
 * Ceiling hit (pre-cutoff count == max_results) signals validate tier 2.
 */
export const executeBlock = async <S>(
  block: BlockDef<S>,
  state: S,
  services: BlockExecutorServices,
  repo: string | null = null,
): Promise<Partial<S>> => {
  const filters = await services.scope({ ...block.opa, repo })
  const vec = await services.embed(block.description)

  // --- Phase 1: pgvector search up to OPA ceiling ---
  const raw = await services.search(
    vec,
    {
      domain: filters.allowed_domains.find((d) => d !== "global"),
      agent_role: block.opa.agent_role,
      task_type: block.opa.task_type,
    },
    filters.max_results,
  )

  // --- Phase 2: distance cutoff — drop irrelevant tail ---
  const relevant = raw.filter((i) => i.distance <= COSINE_DISTANCE_CUTOFF)

  const meta: ContextMeta = {
    ceiling_hit: raw.length >= filters.max_results,
    count: relevant.length,
    dropped: raw.length - relevant.length,
  }

  const enriched = {
    ...state,
    _context: relevant.map((i) => i.text),
    _context_meta: meta,
  }
  return block.execute(enriched as S)
}
