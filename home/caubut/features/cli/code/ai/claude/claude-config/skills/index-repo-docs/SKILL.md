---
name: index-repo-docs
description: Fetch and distill a repo's wiki, docs, and issues into a focused reference doc
argument-hint: "<name-or-url|all> (e.g. git-branchless, git-absorb, all)"
disable-model-invocation: true
---

Fetch documentation from a repository and distill it into a practical reference
doc with concrete recipes and patterns. The output goes to the global claude
config references directory.

## Known Repos

Use this lookup table to resolve short names to repos. If `$ARGUMENTS` doesn't
match a known name, treat it as a GitHub URL or `owner/repo`.

| Name | Repo | Focus |
|------|------|-------|
| `git-branchless` | `arxanas/git-branchless` | Wiki, README, key issues on workflows |
| `git-absorb` | `tummychow/git-absorb` | README, man page, usage patterns |
| `git-revise` | `mystor/git-revise` | README, docs, interactive usage |

If `$ARGUMENTS` is `all`, iterate through every entry in the table above and
run the full indexing process for each one, skipping repos that are up to date.

## Output

Write to: `home/<user>/features/cli/code/ai/claude/claude-config/references/<name>.md`

Where `<user>` is determined from the repo path (check `git config user.name`
or the directory structure). `<name>` is the short name or the repo name from
the URL.

## Incremental Updates

The generated reference doc includes frontmatter with indexing metadata:

```yaml
---
repo: owner/repo
last-indexed: 2026-03-21
repo-head: <commit-sha>
wiki-head: <commit-sha or null>
exclude-issue-patterns:
  - "renovate"
  - "dependabot"
  - "bump version"
---
```

On re-run:

1. **Read the existing reference doc** (if it exists) and parse its frontmatter
2. **Check remote HEADs** for both the repo and wiki:
   ```bash
   repo_head=$(gh api "repos/${owner}/${repo}/commits?per_page=1" --jq '.[0].sha')
   wiki_head=$(git ls-remote "https://github.com/${owner}/${repo}.wiki.git" HEAD 2>/dev/null | cut -f1 || echo "")
   ```
3. **Compare** against `repo-head` and `wiki-head` in the frontmatter
4. **Check for new issues/discussions** updated since `last-indexed`:
   ```bash
   gh api "repos/${owner}/${repo}/issues?sort=reactions-+1&state=all&per_page=10&since=${last_indexed}T00:00:00Z" \
     --jq 'length'
   ```
5. If nothing changed (same HEADs, no new issues), report "already up to date"
   and skip
6. If only issues changed, fetch just the new issues and merge insights into
   the existing doc rather than full regeneration
7. If repo or wiki HEAD changed, do a full regeneration

### Exclude Patterns

The `exclude-issue-patterns` list in frontmatter filters out noise from
issues/discussions. On the first run, initialize it with common bot patterns:
`renovate`, `dependabot`, `bump version`, `release v`.

During indexing, if an issue title matches any pattern (case-insensitive),
skip it. If you encounter a new category of noise issues during distillation,
add the pattern to `exclude-issue-patterns` for future runs.

## Steps

1. **Resolve the repo** from `$ARGUMENTS` using the lookup table above, or
   parse as `owner/repo` or full URL.

2. **Check for incremental update** as described above. If up to date, skip.

3. **Fetch the wiki** (if it exists):
   ```bash
   tmp_dir=$(mktemp -d)
   git clone --depth 1 "https://github.com/${owner}/${repo}.wiki.git" "$tmp_dir/wiki" 2>/dev/null || true
   ```

4. **Fetch the README and docs**:
   ```bash
   gh api "repos/${owner}/${repo}/readme" --jq '.content' | base64 -d > "$tmp_dir/README.md"
   # Also check for docs/ directory
   gh api "repos/${owner}/${repo}/contents/docs" --jq '.[].name' 2>/dev/null | while read f; do
     gh api "repos/${owner}/${repo}/contents/docs/$f" --jq '.content' | base64 -d > "$tmp_dir/docs-$f"
   done
   ```

5. **Fetch key issues/discussions** — top 10 most-reacted, filtered:
   ```bash
   # Use since= for incremental, omit for full reindex
   gh api "repos/${owner}/${repo}/issues?sort=reactions-+1&state=all&per_page=10${since_param}" \
     --jq '.[] | select(.title | test("(renovate|dependabot|bump version|release v)"; "i") | not) |
       "## Issue #\(.number): \(.title)\n\(.body)\n"' > "$tmp_dir/issues.md" 2>/dev/null || true
   ```
   Also check for GitHub Discussions if the repo uses them:
   ```bash
   gh api graphql -f query='
     query { repository(owner:"'"${owner}"'", name:"'"${repo}"'") {
       discussions(first:10, orderBy:{field:UPDATED_AT, direction:DESC}) {
         nodes { title body url }
       }
     }
   }' --jq '.data.repository.discussions.nodes[] |
     "## Discussion: \(.title)\n\(.body)\n\(.url)\n"' >> "$tmp_dir/issues.md" 2>/dev/null || true
   ```

6. **Read all fetched content** and distill into a reference doc with this
   structure:

   ```markdown
   ---
   repo: owner/repo
   last-indexed: <today>
   repo-head: <sha>
   wiki-head: <sha or null>
   exclude-issue-patterns:
     - "renovate"
     - "dependabot"
     - "bump version"
     - "release v"
   ---

   # <Tool Name> Reference

   Distilled from <repo URL>, updated <date>.

   ## Overview
   <1-2 paragraph summary of what the tool does and why>

   ## Installation & Setup
   <How to install, configure, prerequisites>

   ## Core Concepts
   <Key mental models needed to use the tool effectively>

   ## Command Reference
   <Commands with practical examples, grouped by workflow>

   ## Recipes
   <Concrete step-by-step patterns for common tasks, written as numbered
   procedures. These should be copy-pasteable workflows, not abstract
   descriptions. Focus on:
   - The happy path for each common operation
   - How to recover from mistakes
   - Integration with other tools (git-branchless + git-absorb, etc.)>

   ## Anti-Patterns
   <Common mistakes and what to do instead>

   ## Integration
   <How this tool works with the other stacked workflow tools>
   ```

7. **Clean up**:
   ```bash
   rm -rf "$tmp_dir"
   ```

8. **Report** what was generated (full/incremental/skipped), how many source
   files were read, and the output path.

## Guidelines

- Focus on PRACTICAL recipes over theoretical documentation
- Every recipe should be a numbered procedure someone can follow
- Include the exact commands, not just descriptions
- Call out gotchas and edge cases from issues/discussions
- Keep the doc under 500 lines — this is a reference, not a textbook
- If the wiki has workflow guides, prioritize those over API docs
- Preserve and extend `exclude-issue-patterns` across runs — never shrink it
