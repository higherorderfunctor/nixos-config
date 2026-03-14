/**
 * @module workflow
 * Block/pipeline execution model — the core of "scale to millions."
 *
 * This domain defines the block model (typed functions with OPA context),
 * pipeline definitions (YAML-driven DAGs), and the execution engine that
 * wires OPA scoping → pgvector search → instruction injection → block execution.
 *
 * Also contains the Phase 3 RAG workflow (context assembly) which predates
 * the block model but serves the /context endpoint.
 *
 * Public API:
 * - Type exports: {@link BlockDef}, {@link PipelineDef}, {@link OpaContext}, etc.
 * - {@link BlockRegistry} — Effect.Service for block registration and lookup
 * - {@link executeBlock} — generic block execution with OPA injection
 * - {@link buildPipeline} / {@link getCheckpointer} — LangGraph pipeline construction
 * - {@link createContextWorkflow} — Phase 3 RAG workflow
 *
 * Used by: index.ts (HTTP endpoints), meta-workflow (pipeline building)
 */

export type {
  OpaContext,
  BlockDef,
  ConditionalNext,
  PipelineStep,
  PipelineDef,
  InstructionExport,
  PipelineExport,
} from "./Block.js"
export { BlockRegistry } from "./Registry.js"
export { executeBlock } from "./Executor.js"
export type { BlockExecutorServices } from "./Executor.js"
export { getCheckpointer, buildPipeline } from "./Pipeline.js"
export { createContextWorkflow } from "./Workflow.js"
export type { ContextState } from "./Workflow.js"
