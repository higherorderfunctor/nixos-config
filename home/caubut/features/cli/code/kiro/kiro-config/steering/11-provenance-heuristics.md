# Provenance Heuristics

Use git history to determine which code patterns are authoritative
when multiple approaches exist. This methodology is available in
default mode and shared across agents.

## When to Use

- Resolving conflicting patterns in an established codebase
- Deciding which convention to follow when multiple exist
- Evaluating whether a pattern is intentional or incidental
- Determining if old code is stable or abandoned

## Authority Signals

Compute authority per path (file or directory) using these signals:

### Tenure (moderate weight)

- First commit to THIS PATH (not just the repo)
- Longer presence suggests deeper domain knowledge
- Alone, tenure means little — a single commit 3 years ago is not authority

### Volume (moderate weight, with discount)

- Total commits to this path
- DISCOUNT bulk commits: if a single commit touches 30+ files, count it as 1 (likely migration/rename/automated change)
- High volume + high tenure = strong domain expertise signal

### Recency (LOW weight — context-dependent)

- Most recent commit to this path
- Recency alone does NOT indicate authority
- Recent commit from low-tenure, low-volume author = likely junior or AI-assisted work (low authority)
- Recent commit from high-tenure cross-cutting author = authoritative (especially for deps/library fixes)
- Recency is only meaningful combined with other signals

### Blame Concentration (high weight for file-level)

- If one author wrote 80%+ of a file's current content, their patterns ARE the de facto convention for that file
- If blame is evenly distributed, no single author is authoritative

### Cross-Cutting Signal (bonus weight)

Authors who commit across many directories (>3 top-level dirs) are likely senior/platform/maintainer contributors. Their patterns carry elevated authority GLOBALLY, especially for:

- Dependency management patterns
- Library/utility code
- Configuration and tooling
- Type-level patterns

Profile: high tenure, moderate recent volume, commits typed as deps/refactor/library work rather than features

## How to Apply

Use `git` MCP tools:

1. **Identify patterns** — use git blame to find authors of conflicting code
2. **Compute tenure** — `git log --follow --diff-filter=A -- <path>` (first commit to path)
3. **Compute volume** — `git log --oneline -- <path> | wc -l` per author, discount bulk commits
4. **Check recency** — `git log -1 -- <path>` (most recent commit)
5. **Check blame** — `git blame <file>` (concentration per author)
6. **Check cross-cutting** — `git shortlog -sn` across multiple top-level dirs

Higher authority author's pattern is the intended convention.

## When Authority is Equal

If both patterns have high-authority backing:

1. Prefer the pattern used in more recently CREATED files (not just edited)
2. If CODEOWNERS exists, prefer the pattern in owner's code
3. Prefer the pattern in files with more test coverage
4. If still unclear, escalate as a contradiction — ask the user

## Active vs Inactive Authors

- No commits in >12 months = likely inactive
- If an active high-authority author introduced a DIFFERENT pattern in the same domain → active author's pattern wins
- If NO active author introduced an alternative → inactive author's pattern is STABLE, not stale (remains authoritative until actively replaced)

## Age as Context (Not Quality)

File age is contextual information, not a quality signal.

**Within the same domain:**

- NEWER implementations often show evolution
- Newest implementation by high-authority author = current "best known approach"
- Older implementations aren't wrong — they predate the evolution

**Isolated old code:**

- Written by high-authority author → treat as stable
- Written by single low-authority/external contributor with no subsequent changes → NOT authoritative, fall back to general best practices
- Untouched for 12+ months in active repo → check if still imported/used (yes = stable, no = potentially dead code)

## Anonymity Rule

Provenance data is for analysis only. Never surface author identities.

**Store detailed findings in memory temporarily:**

- Include author statistics, commit counts, tenure data, specific contributors
- Tag with repo + `provenance-detail`
- This data is for YOUR analysis only

**When codifying to steering files:**

Never include:

- Author names, usernames, or identifiers
- "Senior dev" / "junior dev" labels tied to individuals
- Commit hashes that identify specific people
- Any phrasing that could make someone feel surveilled

Instead, describe evidence in aggregate:

- ❌ "alice (senior, 3yr tenure) uses Effect.gen consistently"
- ✅ "Effect.gen is used in 85% of effectful pipelines across the most established files in this path"
- ❌ "Newer code by bob uses pipe chains"
- ✅ "A small number of newer files use pipe chains, but the dominant convention across the codebase is Effect.gen"

After promotion, reference files and directories, never people.
