/**
 * @module Block
 * Core type definitions for the block/pipeline model.
 *
 * ARCH: Blocks are typed functions, NOT Effect.Services. Services are for
 * infrastructure (DB, OPA, Embedding). Blocks are domain logic that may use
 * services internally via Effect.runPromise.
 *
 * ARCH: All types are generic over pipeline state `S`. Each pipeline defines
 * its own state shape, and blocks are typed to their pipeline's state.
 */

// ---------------------------------------------------------------------------
// OPA Context — declares what instructions a block needs
// ---------------------------------------------------------------------------

/**
 * OPA context declaration for a block. Sent to OPA scoping endpoint to
 * determine which instructions this block is allowed to see.
 *
 * @example
 * ```ts
 * { agent_role: "workflow-builder", task_type: "authoring", domain: "meta" }
 * ```
 */
export interface OpaContext {
  /** Role the block operates as (e.g., "workflow-builder", "analyst"). */
  readonly agent_role: string
  /** Type of task the block performs (e.g., "routing", "authoring", "analysis"). */
  readonly task_type: string
  /** Knowledge domain the block operates in (e.g., "meta", "effect", "repo"). */
  readonly domain: string
}

// ---------------------------------------------------------------------------
// Block Definition — a single executable step in a pipeline
// ---------------------------------------------------------------------------

/**
 * A block is a named, tagged, OPA-scoped function that transforms pipeline state.
 * Generic over `S` — the pipeline's state type.
 *
 * ARCH: Blocks are LangGraph node functions. The block executor wraps them to
 * inject OPA-scoped instructions into state as `_context` before execution.
 *
 * @typeParam S - Pipeline state type. Each pipeline defines its own shape.
 */
export interface BlockDef<S> {
  /** Unique identifier, used as LangGraph node name and YAML filename. */
  readonly id: string
  /** Human-readable name for display and search. */
  readonly name: string
  /** What this block does — also used as the embedding query for instruction search. */
  readonly description: string
  /** Searchable tags for BlockRegistry discovery. */
  readonly tags: ReadonlyArray<string>
  /** OPA context — determines which instructions this block receives. */
  readonly opa: OpaContext
  /** Execute the block, returning partial state updates. */
  readonly execute: (state: S) => Promise<Partial<S>>
}

// ---------------------------------------------------------------------------
// Pipeline Definition — ordered sequence of blocks
// ---------------------------------------------------------------------------

/** Conditional routing target for branching pipelines. */
export interface ConditionalNext {
  /** Condition expression evaluated against state. */
  readonly condition: string
  /** Block to route to if condition is true. */
  readonly block_id: string
}

/** A single step in a pipeline — references a block by ID with optional routing. */
export interface PipelineStep {
  /** ID of the block to execute at this step. */
  readonly block_id: string
  /** Optional condition for whether this step executes. */
  readonly condition?: string
  /** Next step: string for linear, array for conditional branching. */
  readonly next?: string | ReadonlyArray<ConditionalNext>
}

/**
 * A pipeline is an ordered sequence of blocks with routing logic.
 * Generic over `S` — all blocks in the pipeline share this state type.
 *
 * ARCH: PipelineDef is the declarative description. PipelineExecutor builds
 * a LangGraph StateGraph from it at runtime.
 */
export interface PipelineDef<S> {
  /** Unique identifier for this pipeline. */
  readonly id: string
  /** Human-readable name. */
  readonly name: string
  /** What this pipeline does. */
  readonly description: string
  /** Ordered steps — each references a block by ID. */
  readonly steps: ReadonlyArray<PipelineStep>
  /** Default state values before first block executes. */
  readonly initial_state: Partial<S>
}

// ---------------------------------------------------------------------------
// Export Types — YAML shapes for Nix reproducibility (UC-MW-16)
// ---------------------------------------------------------------------------

/**
 * Structured output for AI-orchestrated blocks (UC-MW-21).
 *
 * When Claude calls block MCP tools in a loop (Sequential Thinking pattern),
 * each block returns this shape so Claude can reason about next steps and
 * decide the next MCP call.
 *
 * ARCH: Only used by blocks with execution_env "ai-orchestrated". Inline and
 * subagent blocks return plain state updates via BlockDef.execute.
 */
export interface BlockOutput {
  /** Summary of what the block accomplished. */
  readonly what_was_done: string
  /** The actual result data (block-specific shape). */
  readonly result: unknown
  /** Structured signal for what Claude should do next (UC-MW-21, Q2). */
  readonly next_step: NextStep
  /** Decisions that need human input before proceeding. */
  readonly human_decisions_needed: ReadonlyArray<string>
}

/**
 * Discriminated union for BlockOutput.next_step (Q2 resolution).
 *
 * Claude maps each variant to a specific action:
 * - resume → call run_workflow with same thread_id (next deterministic segment)
 * - spawn_subagent → call use_subagent, inspect result, then resume
 * - ask_user → present question to user, pass answer back when resuming
 * - complete → workflow done, present summary
 *
 * Design follows Sequential Thinking MCP pattern: structured outputSchema that
 * Claude parses to decide its next action. No free text interpretation needed.
 *
 * References:
 * - Sequential Thinking MCP: https://www.npmjs.com/package/@modelcontextprotocol/server-sequential-thinking
 * - Anthropic advanced tool use: https://www.anthropic.com/engineering/advanced-tool-use
 */
export type NextStep =
  | NextStepResume
  | NextStepSpawnSubagent
  | NextStepAskUser
  | NextStepComplete

/** Continue to next deterministic segment. */
export interface NextStepResume {
  readonly type: "resume"
  /** Optional hint about what the next segment will do (for UX framing). */
  readonly context?: string
}

/** Spawn a subagent before resuming. Claude calls use_subagent. */
export interface NextStepSpawnSubagent {
  readonly type: "spawn_subagent"
  /** Agent name from workflow's agent config. */
  readonly agent: string
  /** Task description for the subagent. */
  readonly task: string
}

/** Ask user a question before resuming. */
export interface NextStepAskUser {
  readonly type: "ask_user"
  /** The question to present. */
  readonly question: string
  /** Optional structured choices (if omitted, open-ended). */
  readonly options?: ReadonlyArray<string>
}

/** Workflow complete. */
export interface NextStepComplete {
  readonly type: "complete"
  /** Summary of what the workflow accomplished. */
  readonly summary: string
}

/**
 * YAML export shape for a single instruction.
 * ARCH: Vectors are NOT exported — they're re-embedded at load time from the
 * same model, ensuring consistency. Only source data is persisted to disk.
 */
export interface InstructionExport {
  /** Instruction identifier (maps to deterministic UUID in DB). */
  readonly id: string
  /** The instruction text that gets injected into block context. */
  readonly text: string
  /** OPA metadata — determines which blocks can see this instruction. */
  readonly metadata: {
    readonly agent_role: string
    readonly task_type: string
    readonly domain: string
    readonly repo: string | null
  }
  /** MD5 of text field — used for change detection during YAML → DB loading. */
  readonly content_hash: string
}

/** YAML export shape for a pipeline definition. */
export interface PipelineExport {
  /** Pipeline identifier. */
  readonly id: string
  /** Human-readable name. */
  readonly name: string
  /** Ordered steps with routing. */
  readonly steps: ReadonlyArray<PipelineStep>
}
