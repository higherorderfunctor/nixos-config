import type { BlockDef } from "./Block.js"
import type { ScopingInput, ScopingFilters } from "./Opa.js"
import type { Instruction, SearchFilters } from "./InstructionRepo.js"

export interface BlockExecutorServices {
  readonly scope: (input: ScopingInput) => Promise<ScopingFilters>
  readonly embed: (text: string) => Promise<ReadonlyArray<number>>
  readonly search: (
    embedding: ReadonlyArray<number>,
    filters: SearchFilters,
    limit: number,
  ) => Promise<ReadonlyArray<Instruction>>
}

export const executeBlock = async <S>(
  block: BlockDef<S>,
  state: S,
  services: BlockExecutorServices,
): Promise<Partial<S>> => {
  const filters = await services.scope({ ...block.opa, repo: null })
  const vec = await services.embed(block.description)
  const instructions = await services.search(
    vec,
    {
      domain: filters.allowed_domains.find((d) => d !== "global"),
      agent_role: block.opa.agent_role,
      task_type: block.opa.task_type,
    },
    filters.max_results,
  )

  const enriched = { ...state, _context: instructions.map((i) => i.text) }
  return block.execute(enriched as S)
}
