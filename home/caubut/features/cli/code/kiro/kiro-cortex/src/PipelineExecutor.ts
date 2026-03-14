/**
 * @module PipelineExecutor
 * Builds LangGraph StateGraphs from pipeline definitions at runtime.
 *
 * ARCH: Given a PipelineDef, constructs a StateGraph where each node is a block
 * wrapped by the BlockExecutor (OPA scoping → pgvector → inject → execute).
 * PG checkpointer enables interrupt/resume for HITL workflows.
 *
 * CONSTRAINT: The `CompiledPipeline` type uses `any` because LangGraph's
 * CompiledStateGraph generic params depend on dynamic node registration.
 * This is the one approved `as any` exception in the codebase.
 */

import { StateGraph, type Annotation, START, END, type CompiledStateGraph } from "@langchain/langgraph"
import { PostgresSaver } from "@langchain/langgraph-checkpoint-postgres"
import type { BlockDef, PipelineDef } from "./Block.js"
import { executeBlock, type BlockExecutorServices } from "./BlockExecutor.js"

const CONN_STRING = "postgresql://localhost:5435/kiro_cortex"

/** Singleton PG checkpointer — created once, reused across all pipelines. */
let _checkpointer: PostgresSaver | null = null

/**
 * Get or create the PG checkpointer for LangGraph state persistence.
 * ARCH: Singleton pattern — LangGraph checkpointer manages its own connection pool.
 */
export const getCheckpointer = async (): Promise<PostgresSaver> => {
  if (!_checkpointer) {
    _checkpointer = PostgresSaver.fromConnString(CONN_STRING)
    await _checkpointer.setup()
  }
  return _checkpointer
}

// eslint-disable-next-line @typescript-eslint/no-explicit-any -- CompiledStateGraph generic params depend on dynamic node registration
type CompiledPipeline = CompiledStateGraph<any, any, any, any>

/**
 * Build a LangGraph StateGraph from a pipeline definition.
 *
 * Each block is wrapped by the BlockExecutor so it receives OPA-scoped
 * instructions before execution. Steps are wired linearly (START → step1 → step2 → ... → END).
 *
 * @param definition - The pipeline definition (steps, routing).
 * @param annotation - LangGraph Annotation.Root for the state type.
 * @param blocks - Map of block ID → BlockDef, must contain all referenced blocks.
 * @param services - Async service wrappers for OPA, Embedding, InstructionRepo.
 * @returns Compiled LangGraph StateGraph with PG checkpointer.
 */
export const buildPipeline = async <S>(
  definition: PipelineDef<S>,
  annotation: ReturnType<typeof Annotation.Root<any>>,
  blocks: ReadonlyMap<string, BlockDef<S>>,
  services: BlockExecutorServices,
): Promise<CompiledPipeline> => {
  const { steps } = definition

  // --- Register all blocks as LangGraph nodes, wrapped by block executor ---
  const nodeMap: Record<string, (state: S) => Promise<Partial<S>>> = {}
  for (const step of steps) {
    const block = blocks.get(step.block_id)
    if (!block) throw new Error(`Block not found: ${step.block_id}`)
    // ARCH: Each node goes through executeBlock for OPA-scoped instruction injection
    nodeMap[step.block_id] = (state: S) => executeBlock(block, state, services)
  }

  const builder = new StateGraph(annotation).addNode(nodeMap)

  // --- Wire linear edges: START → first → second → ... → END ---
  builder.addEdge(START, steps[0]!.block_id)
  for (let i = 0; i < steps.length; i++) {
    const target = i < steps.length - 1 ? steps[i + 1]!.block_id : END
    builder.addEdge(steps[i]!.block_id, target)
  }

  const checkpointer = await getCheckpointer()
  return builder.compile({ checkpointer })
}
