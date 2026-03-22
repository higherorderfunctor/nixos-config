# Memory (OpenMemory)

## Available Tools

- `openmemory_store` — save a new memory
- `openmemory_query` — semantic search for relevant memories
- `openmemory_list` — list memories with filters
- `openmemory_get` — retrieve a specific memory by ID
- `openmemory_reinforce` — strengthen or update an existing memory

## CRITICAL: Scoping Rules

- **user_id**: set to "caubut" on every call
- **tags**: ALWAYS include a tag for the git repository identity

## Memory Types (for openmemory_store)

OpenMemory MCP wrapper uses a `type` parameter to distinguish between storage systems:

- `contextual` — HSG memory system (decisions, conventions, patterns, workflow preferences)
- `factual` — Temporal graph system (subject-predicate-object facts with validity periods)
- `both` — Store in both HSG and temporal graph systems

When in doubt, use `contextual`.

**Note on Sectors**: OpenMemory automatically classifies memories into sectors (episodic, semantic, procedural, emotional, reflective) based on content analysis. These are internal classifications within the HSG system - you don't specify them, they're assigned automatically.

## Parameter Validation

**type parameter (openmemory_store):**
- ✅ Valid: "contextual", "factual", "both"
- ❌ Invalid: "procedural", "semantic", "episodic" (these are auto-assigned sectors, not types)

**Common mistakes:**
- ❌ `type="procedural"` → ✅ `type="contextual"` (sector assigned automatically)
- ❌ Mixing query parameters → ✅ Use `k` for limit, `query` for search text
- ❌ Missing user_id → ✅ Always set `user_id="caubut"`

**Before storing, verify:**
- type is one of three valid values
- tags include repo/workspace identifier
- user_id is set

## Determining the Project Tag

1. Use the `git` MCP to get the remote origin URL
2. Extract the repo name
   (e.g., `git@github.com:org/repo.git` → `org/repo`)
3. Include that as a tag when storing AND filtering when searching
4. If no remote exists, use the git common directory path
5. If not in a git repo, use the tag `global`

## Tag Examples

- Worktree at `~/code/my-repo/` → tags: `["org/my-repo"]`
- Worktree at `~/code/my-repo-feat-x/` → tags: `["org/my-repo"]` (SAME)
- Non-git directory → tags: `["global"]`
- Universal preferences → tags: `["global", "preferences"]`
- Include **version numbers** in tags for dependency-specific facts
  (e.g., `["org/repo", "effect-3.x"]`)

## When to Search Memory

- **Before starting any task** — always check first (Tier 2+)
- **Before any web search or GitHub lookup** — avoid redundant searches
- When the user references something from a previous session

## When to Store

- Architectural decisions and their rationale (`contextual`)
- Library API behavior discovered from source reading (`factual`)
- Workarounds found in GitHub issues (`both`)
- Project conventions and patterns (`contextual`)
- API endpoints, versions, config values (`factual`)
- Search results that answered a hard question (`factual`)
- Always distill to the useful fact first — do not store raw search output

## When to Reinforce

Use `openmemory_reinforce` when:

- You re-confirm an existing fact through a new source
- A previous finding is still accurate in a newer version
- The user explicitly confirms a stored decision is still valid

## Staleness Detection

If you discover information that contradicts a stored memory:

- Store the NEW fact with current version tags
- Tell the user: "I found a stored memory that may be outdated:
  [summary]. Current information says [new finding]. Should I
  update this?"
- Do NOT silently delete or overwrite — always ask first
- When a major version changes, old version-tagged memories are
  suspect — flag them when encountered

## Content Length Guidelines

**IMPORTANT**: OpenMemory defaults to truncating content at 200 characters. Your config disables this (`OM_USE_SUMMARY_ONLY=false`), but be aware:

- Store complete, self-contained information
- Don't rely on external context that might be lost
- For very long content (>2000 chars), consider breaking into multiple focused memories
- Each memory should be independently useful

## What NOT to Store

- Trivial implementation details
- Temporary workarounds (unless explicitly asked)
- Information already captured in `.kiro/steering/` files
- Raw search results — distill to the useful fact first
