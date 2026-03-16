/**
 * @module kiro-cortex
 *
 * Workflow orchestration platform — structured instructions in PostgreSQL/pgvector,
 * governed by OPA policies, orchestrated via the segment model (deterministic
 * LangGraph segments stitched by Claude at AI boundaries).
 *
 * Entry points:
 * - src/main.ts  — HTTP API server (port 3100)
 * - src/mcp.ts   — MCP stdio server (imports main.ts, starts backend automatically)
 *
 * No public exports — this package runs as a service, not a library.
 */
