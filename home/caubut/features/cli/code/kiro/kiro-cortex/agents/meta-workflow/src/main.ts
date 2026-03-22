// ARCH: Meta-workflow agent entry point. Imports kiro-cortex as a library,
// registers the meta-workflow graph, and starts the MCP server.
import { startMcpServer } from "kiro-cortex"
import { buildMetaWorkflow } from "./graph.js"

startMcpServer([{
  id: "meta-workflow",
  name: "meta-workflow",
  description: "Build, update, and refine workflows",
  build: buildMetaWorkflow,
}])
