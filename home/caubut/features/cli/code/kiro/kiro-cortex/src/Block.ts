// --- OPA Context ---

export interface OpaContext {
  readonly agent_role: string
  readonly task_type: string
  readonly domain: string
}

// --- Block Definition ---

export interface BlockDef<S> {
  readonly id: string
  readonly name: string
  readonly description: string
  readonly tags: ReadonlyArray<string>
  readonly opa: OpaContext
  readonly execute: (state: S) => Promise<Partial<S>>
}

// --- Pipeline Definition ---

export interface ConditionalNext {
  readonly condition: string
  readonly block_id: string
}

export interface PipelineStep {
  readonly block_id: string
  readonly condition?: string
  readonly next?: string | ReadonlyArray<ConditionalNext>
}

export interface PipelineDef<S> {
  readonly id: string
  readonly name: string
  readonly description: string
  readonly steps: ReadonlyArray<PipelineStep>
  readonly initial_state: Partial<S>
}

// --- Export Types (YAML shapes for UC-MW-16) ---

export interface InstructionExport {
  readonly id: string
  readonly text: string
  readonly metadata: {
    readonly agent_role: string
    readonly task_type: string
    readonly domain: string
    readonly repo: string | null
  }
  readonly content_hash: string
}

export interface PipelineExport {
  readonly id: string
  readonly name: string
  readonly steps: ReadonlyArray<PipelineStep>
}
