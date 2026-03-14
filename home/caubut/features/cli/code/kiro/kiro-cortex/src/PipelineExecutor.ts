import { StateGraph, type Annotation, START, END, type CompiledStateGraph } from "@langchain/langgraph"
import { PostgresSaver } from "@langchain/langgraph-checkpoint-postgres"
import type { BlockDef, PipelineDef } from "./Block.js"
import { executeBlock, type BlockExecutorServices } from "./BlockExecutor.js"

const CONN_STRING = "postgresql://localhost:5435/kiro_cortex"

let _checkpointer: PostgresSaver | null = null

export const getCheckpointer = async (): Promise<PostgresSaver> => {
  if (!_checkpointer) {
    _checkpointer = PostgresSaver.fromConnString(CONN_STRING)
    await _checkpointer.setup()
  }
  return _checkpointer
}

// eslint-disable-next-line @typescript-eslint/no-explicit-any -- CompiledStateGraph generic params depend on dynamic node registration
type CompiledPipeline = CompiledStateGraph<any, any, any, any>

export const buildPipeline = async <S>(
  definition: PipelineDef<S>,
  annotation: ReturnType<typeof Annotation.Root<any>>,
  blocks: ReadonlyMap<string, BlockDef<S>>,
  services: BlockExecutorServices,
): Promise<CompiledPipeline> => {
  const { steps } = definition

  const nodeMap: Record<string, (state: S) => Promise<Partial<S>>> = {}
  for (const step of steps) {
    const block = blocks.get(step.block_id)
    if (!block) throw new Error(`Block not found: ${step.block_id}`)
    nodeMap[step.block_id] = (state: S) => executeBlock(block, state, services)
  }

  const builder = new StateGraph(annotation).addNode(nodeMap)

  builder.addEdge(START, steps[0]!.block_id)
  for (let i = 0; i < steps.length; i++) {
    const target = i < steps.length - 1 ? steps[i + 1]!.block_id : END
    builder.addEdge(steps[i]!.block_id, target)
  }

  const checkpointer = await getCheckpointer()
  return builder.compile({ checkpointer })
}
