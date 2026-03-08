# Personal Agents

Quick reference for personal agent configurations and workflows.

## Overview

Personal agents extend Kiro's capabilities with specialized workflows. Agents are defined in `~/.kiro/agents/` (symlinked from this directory) and available globally across all workspaces.

## Available Agents

### Ideation Agent
**Purpose:** Open-ended exploration, research, and prompt generation  
**Shortcut:** `Ctrl+Shift+I`  
**Capabilities:** Web search, codebase analysis, memory integration, read-only  
**Use when:** Exploring options, researching approaches, generating execution prompts

### Planner Agent (Built-in)
**Purpose:** Structured task breakdown and implementation planning  
**Shortcut:** `Shift+Tab` or `/plan`  
**Capabilities:** Requirements gathering, codebase exploration, automatic handoff  
**Use when:** Clear goal but need structured breakdown

### Default Agent (Built-in)
**Purpose:** General execution and file modifications  
**Shortcut:** Default (no switch needed)  
**Capabilities:** Full toolset including file writes and command execution  
**Use when:** Direct execution with clear instructions

## Keyboard Shortcuts

| Shortcut | Agent | Action |
|----------|-------|--------|
| `Ctrl+Shift+I` | Ideation | Switch to ideation mode |
| `Shift+Tab` | Planner | Toggle planner mode |
| `/agent swap <name>` | Any | Switch to specific agent |
| `/model` | Any | Change model mid-session |

## Workflow Patterns

### Pattern 1: Research → Execute
```
1. Ctrl+Shift+I (Ideation) → Research and explore
2. Review generated prompt
3. Switch to Default → Execute directly
```

### Pattern 2: Research → Plan → Execute
```
1. Ctrl+Shift+I (Ideation) → Research and explore
2. Review generated prompt
3. Shift+Tab (Planner) → Structured breakdown
4. Approve plan → Automatic execution handoff
```

### Pattern 3: Direct Execution
```
1. Default agent → Execute immediately
   (Skip ideation/planning when approach is clear)
```

## Model Selection

Agents can specify default models or use `auto` for automatic optimization:

- **auto** (1.00x) - Automatic model selection per task
- **claude-haiku-4.5** (0.40x) - Fast, economical
- **claude-sonnet-4** (1.30x) - Hybrid reasoning/coding
- **claude-opus-4.5** (2.20x) - Maximum reasoning

Switch models mid-session: `/model <model-name>`

## When to Use Which Agent

| Question | Agent |
|----------|-------|
| "I don't know what I don't know" | Ideation |
| "What are my options?" | Ideation |
| "What's the best approach?" | Ideation |
| "I know what to build" | Planner |
| "Break this down into steps" | Planner |
| "Just do this" | Default |

## Agent Suggestions

Kiro will suggest switching agents when appropriate (see `13-ideation-workflow.md`):
- Default agent detects open-ended questions → suggests Ideation
- Ideation agent completes research → suggests Planner or Default
- Planner completes breakdown → automatic handoff to execution

## Adding New Agents

1. Create `~/.kiro/agents/<name>.json` (or in this directory for NixOS management)
2. Define agent configuration (see [Agent Configuration docs](https://kiro.dev/docs))
3. Add to `default.nix` agentFiles list (if using NixOS)
4. Restart Kiro or use `/agent swap <name>`

## Configuration

Personal agents are managed via NixOS Home Manager in this repository:
- **Agent configs:** `kiro-config/agents/*.json`
- **Symlinked to:** `~/.kiro/agents/`
- **Managed by:** `default.nix`

Changes to agent configs are immediate (symlinked). Changes to `default.nix` require `home-manager switch`.
