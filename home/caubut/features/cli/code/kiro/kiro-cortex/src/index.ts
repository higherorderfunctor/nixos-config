/**
 * @module kiro-cortex
 *
 * Workflow orchestration platform — structured instructions in PostgreSQL/pgvector,
 * governed by OPA policies, orchestrated via the segment model (deterministic
 * LangGraph segments stitched by Claude at AI boundaries).
 *
 * Public API for agent packages:
 * - `startMcpServer(workflows)` — launch MCP stdio server with registered workflows
 * - Service layers: SqlLive, opaLayer, embeddingLayer, instructionLayer, registryLayer
 * - `loadInstructions` — seed DB from YAML at startup
 */

export { SqlLive } from "./Sql.js"
export { layer as opaLayer } from "./opa/index.js"
export { layer as embeddingLayer } from "./embedding/index.js"
export { layer as instructionLayer, loadInstructions } from "./instruction/index.js"
export { registryLayer } from "./workflow/index.js"
export { startMcpServer, type WorkflowDef } from "./mcp.js"
