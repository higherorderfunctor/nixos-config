
# Agents

This directory contains personal Kiro agent definitions.
Agents are activated explicitly via `/agent <name>` in Kiro CLI.

Unlike steering files (which are always loaded), agents define
specialized personas and workflows for specific task types.

## Usage

Place `.md` files here defining agent behavior. Each file becomes
an available agent. Activate with:

`/agent <filename-without-extension>`

## Guidelines

- Agents should reference shared steering files (e.g.,
  11-provenance-heuristics.md) rather than duplicating methodology
- Keep agents focused on a single task domain
- Workspace-specific agents belong in the workspace repo's
  `.kiro/agents/`, not here
