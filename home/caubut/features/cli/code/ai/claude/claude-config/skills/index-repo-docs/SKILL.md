---
name: index-repo-docs
description: Fetch and distill a repo's wiki, docs, and issues into a focused reference doc
argument-hint: "<name-or-url> (e.g. git-branchless, git-absorb, github.com/org/repo)"
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

## Output

Write to: `home/<user>/features/cli/code/ai/claude/claude-config/references/<name>.md`

Where `<user>` is determined from the repo path (check `git config user.name`
or the directory structure). `<name>` is the short name or the repo name from
the URL.

If the file already exists, replace it entirely with the updated version.

## Steps

1. **Resolve the repo** from `$ARGUMENTS` using the lookup table above, or
   parse as `owner/repo` or full URL.

2. **Fetch the wiki** (if it exists):
   ```bash
   tmp_dir=$(mktemp -d)
   git clone --depth 1 "https://github.com/${owner}/${repo}.wiki.git" "$tmp_dir/wiki" 2>/dev/null || true
   ```

3. **Fetch the README and docs**:
   ```bash
   gh api "repos/${owner}/${repo}/readme" --jq '.content' | base64 -d > "$tmp_dir/README.md"
   # Also check for docs/ directory
   gh api "repos/${owner}/${repo}/contents/docs" --jq '.[].name' 2>/dev/null | while read f; do
     gh api "repos/${owner}/${repo}/contents/docs/$f" --jq '.content' | base64 -d > "$tmp_dir/docs-$f"
   done
   ```

4. **Fetch key issues/discussions** (optional, top 10 most-reacted):
   ```bash
   gh api "repos/${owner}/${repo}/issues?sort=reactions-+1&state=all&per_page=10" \
     --jq '.[] | "## Issue #\(.number): \(.title)\n\(.body)\n"' > "$tmp_dir/issues.md" 2>/dev/null || true
   ```

5. **Read all fetched content** and distill into a reference doc with this
   structure:

   ```markdown
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

6. **Clean up**:
   ```bash
   rm -rf "$tmp_dir"
   ```

7. **Report** what was generated, how many source files were read, and the
   output path.

## Guidelines

- Focus on PRACTICAL recipes over theoretical documentation
- Every recipe should be a numbered procedure someone can follow
- Include the exact commands, not just descriptions
- Call out gotchas and edge cases from issues/discussions
- Keep the doc under 500 lines — this is a reference, not a textbook
- If the wiki has workflow guides, prioritize those over API docs
