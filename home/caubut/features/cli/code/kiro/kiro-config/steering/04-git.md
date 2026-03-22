# Git

Use the `git` MCP tools for all local git operations rather than raw
shell commands. This includes diffs, file history, commit logs, file
contents at specific revisions, branches, tags, and status.

Prefer the git MCP over shell `git` commands — it provides structured
output that is easier to reason about.

## Commit Message Convention

Use **Conventional Commits** format by default:

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types**: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`, `perf`, `ci`, `build`, `revert`

**Scope**: Optional, indicates area of change (e.g., `steering`, `mcp`, `config`)

**Subject**: Imperative mood, lowercase, no period

**Body**: Optional, explain what and why (not how)

**Footer**: Optional, breaking changes or issue references

**Examples**:
- `feat(steering): add thinking depth methodology`
- `fix(mcp): correct AWS credential validation`
- `docs: update repository structure guide`

**Workspace Override**: If a workspace has its own commit convention (check `.kiro/steering/` or project docs), adopt that instead.

## Git Worktree Awareness

The user frequently uses **git worktrees**. Multiple working directories
may point to the same repository. When determining repository identity:

1. Use the `git` MCP to inspect the remote origin URL
2. Extract the repo identifier
   (e.g., `git@github.com:org/repo.git` → `org/repo`)
3. If no remote exists, the common git dir is the stable identifier

Never assume directory name equals project name.

## When to Use Git MCP

- Reading file contents at specific revisions
- Comparing changes across branches or commits
- Inspecting commit history and authorship
- Determining repository identity for memory scoping
- Supporting code provenance analysis (see 11-provenance-heuristics.md)
