import { Command } from "@langchain/langgraph"
import type { MetaWorkflowStateType } from "./state.js"

export const routeNode = (state: MetaWorkflowStateType): Command =>
  new Command({ goto: state.mode === "refine" ? "author" : "interview" })
