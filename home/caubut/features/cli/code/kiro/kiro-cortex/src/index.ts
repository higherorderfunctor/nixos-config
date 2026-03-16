/**
 * @module kiro-cortex
 *
 * Workflow orchestration platform — structured instructions in PostgreSQL/pgvector,
 * governed by OPA policies, orchestrated via the segment model (deterministic
 * LangGraph segments stitched by Claude at AI boundaries).
 *
 * Entry point:
 * - src/mcp.ts — MCP stdio server (@effect/ai McpServer.layerStdio)
 *
 * No public exports — this package runs as a service, not a library.
 */
