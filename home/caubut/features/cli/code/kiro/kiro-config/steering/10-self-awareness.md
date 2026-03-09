# Self-Awareness

## Session Bootstrap

At the start of a session in a workspace, if you haven't already,
read the `.kiro/` directory structure using the `git` MCP or file
tools. Understand:

- What workspace MCPs are configured (`.kiro/settings/mcp.json`)
- What steering files exist and their content
- What agents are defined (`.kiro/agents/`)
- What workspace-level overrides are in place

For personal steering (`~/.kiro/steering/`), also check:
- `migrations/` - Recent pattern changes or transitions in progress
- `_archive/` - Deprecated patterns (historical reference)

This lets you adapt your behavior to the workspace context and
identify gaps (e.g., MCPs without steering guidance). Understanding
migrations helps you know what's changing vs stable.

## Steering File Loading Strategy

Not all steering files are relevant to every task. Use progressive
disclosure to manage context:

### Small workspaces (≤10 steering files)

Read all steering files at session start. Context cost is low.

### Large workspaces (>10 steering files)

1. Read file NAMES and any leading comment/header first to
   understand what each file covers
2. Read full content only for files relevant to the current task
3. If a task spans multiple domains, load those domain files
4. Do not load every steering file into context by default

### Relevance signals

Use these to decide which files to fully load:

- File name matches the current task domain
- File header/comment describes applicability
  (e.g., `<!-- Applies when: working in packages that depend on effect -->`)
- Agent definition scopes the file to a domain you're working in
- User explicitly references a convention or domain

### Personal steering files

Always load fully — they define the operating framework
(research protocol, IP protection, memory lifecycle). These
are small in number and universally applicable.

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
- Whether CODEOWNERS exists (may be used by workspace agents for team boundary detection)
- What technology stack the project uses
- What migrations are in progress
- What conventions are already codified in steering

## Dynamic Steering Discovery

Personal steering files define WHAT to do (research protocol,
memory lifecycle, IP protection). Workspace steering files define
HOW to apply it in this specific repo (conventions, analysis rules,
domain-specific protocols).

When a task maps to a capability described in personal steering:

1. Check if the workspace has steering files that extend or
   specialize that capability for this repo
2. If workspace steering exists for the current task domain,
   follow it — workspace steering takes precedence for
   repo-specific behavior
3. If no workspace steering exists for the task, fall back to
   personal steering defaults
4. Never assume a workspace steering file exists by name —
   discover what's available by reading .kiro/steering/

Examples:

- Personal steering says "use tiered research protocol"
- Workspace steering may add repo-specific research rules
  (e.g., analysis protocols, migration awareness, domain scoping)
- Kiro reads both layers and merges: personal defines the
  framework, workspace defines the local specialization

## Nix-Managed Symlinks (Personal Config Only)

Personal Kiro config files (`~/.kiro/`) are managed by home-manager and symlinked to the Nix store. Workspace config (`.kiro/` in projects) uses real files.

**Symlinked paths (personal only):**
- `~/.kiro/steering/*.md`
- `~/.kiro/settings/mcp.json`
- `~/.kiro/agents/*.json` (declarative configs)

**Real files (user runtime):**
- `~/.kiro/settings/cli.json`
- `~/.kiro/sessions/`
- `~/.kiro/.cli_bash_history`

**Reading symlinked files:**

The `fs_read` tool fails on symlinks. Use the shell tool to resolve with `readlink -f`:

```bash
readlink -f ~/.kiro/steering/14-ollama-models.md | xargs cat
```

**Why symlinks exist:**

Using `mkOutOfStoreSymlink` allows editing source files in `~/Documents/projects/nixos-config/home/caubut/features/cli/code/kiro/kiro-config/` without rebuilding. The symlink chain goes: `~/.kiro/steering/*.md` → `/nix/store/.../hm_*.md` → source file. Changes are immediately visible.

**Detection:**

If reading a personal config file fails, it's likely a symlink. Fall back to shell with `readlink -f`.
