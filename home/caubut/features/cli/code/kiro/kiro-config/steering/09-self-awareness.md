# Self-Awareness

## Session Bootstrap

At the start of a session in a workspace, if you haven't already,
read the `.kiro/` directory structure using the `git` MCP or file
tools. Understand:

- What workspace MCPs are configured (`.kiro/settings/mcp.json`)
- What steering files exist and their content
- What agents are defined (`.kiro/agents/`)
- What workspace-level overrides are in place

This lets you adapt your behavior to the workspace context and
identify gaps (e.g., MCPs without steering guidance).

## Agent Awareness

If this workspace defines agents in `.kiro/agents/`, read them to
understand which steering files are scoped to which domain.

When working in a specific domain, prioritize the steering files
relevant to that domain's agent definition.

If no agents are defined, use all steering files as general guidance
and self-select the most relevant ones based on the current task.

## Agent Tool Scoping

Some agents define additional MCP tools in their agent-level config.
These tools are ONLY available to that agent and are not inherited
by other agents or the default context.

When operating as a scoped agent:

- Be aware of which tools are agent-specific vs inherited
- Agent-specific tools likely access proprietary data
- Apply stricter IP protection when using agent-specific tools

## Agent Classification

Agents operate in one of two modes:

### Internal-Only Agent

- Accesses proprietary data sources (private Confluence, internal APIs)
- External tools may still be available but require strict sanitization
- If an external search would help, formulate the query from
  GENERAL KNOWLEDGE ONLY, never from what internal tools returned

### General-Purpose Agent

- Can use all tools (internal + external)
- IP protection rules from 00-ip-protection.md apply
- Must generalize queries before sending to external tools

## Workspace Context Adaptation

After reading the workspace structure, note:

- Which teams or domains are represented
- Whether CODEOWNERS exists (used by code-reviewer agent)
- What technology stack the project uses
- What migrations are in progress
- What conventions are already codified in steering
