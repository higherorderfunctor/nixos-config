---
name: stack-restack
description: Restructure a range of commits into a clean, atomic stack ordered by concern
argument-hint: "<range> (e.g. main..HEAD, branch-name, hash1..hash2)"
---

Restructure a range of existing commits into a clean stack of atomic commits
grouped by concern. The input is a commit range — anything `git diff` and
`git log` understand (branch name, `main..HEAD`, `hash1..hash2`, etc.).

## Steps

1. **Check branchless init**:
   ```bash
   if [ ! -d ".git/branchless" ]; then git branchless init; fi
   ```

2. **Parse the range** from `$ARGUMENTS`. Common forms:
   - `main..HEAD` or `main..` — everything since main
   - `<branch>` — the branch tip vs its merge-base with main
   - `<hash1>..<hash2>` — explicit range
   - `<hash>..HEAD` — from a specific commit to current

   Resolve to a `<base>` and `<tip>`:
   ```bash
   # For range syntax (base..tip):
   BASE=<resolved base>
   TIP=<resolved tip>

   # For a branch name, find the merge-base:
   BASE=$(git merge-base main <branch>)
   TIP=<branch>
   ```

3. **Understand the current state**. Run all of these:
   ```bash
   git sl
   git log --oneline $BASE..$TIP
   git diff --stat $BASE..$TIP
   git diff $BASE..$TIP
   ```
   Read the full diff carefully. Count the total lines changed.

4. **Analyze and classify every change** into logical groups. Standard ordering:
   1. Refactoring / cleanup (renames, moves, formatting — no behavior change)
   2. Dependencies / build config changes
   3. Scaffolding / types / interfaces / schemas
   4. Core business logic (the main feature or fix)
   5. Edge cases / error handling
   6. Tests
   7. Documentation / config

   For each group, note:
   - Which files and hunks belong to it
   - A one-sentence commit message
   - Estimated line count (target 50-200 per commit)

   If a file has changes spanning multiple groups, it will need `git add -p`
   to split hunks across commits.

5. **Present the plan** to the user. Format as a numbered list:
   ```
   Proposed stack (N commits, M total lines):

   1. refactor(scope): description — files X, Y (~80 lines)
   2. feat(scope): add types — files A, B (~120 lines)
   3. feat(scope): core logic — files C, D, E (~150 lines)
   ...
   ```
   **Wait for user approval.** Adjust if they have feedback on grouping or
   ordering.

6. **Check for uncommitted work** before starting:
   ```bash
   git status --short
   ```
   If there are uncommitted changes, warn the user and ask whether to stash
   or commit them first.

7. **Flatten the range** into the working tree:
   ```bash
   git reset --soft $BASE
   git restore --staged .
   ```
   This uncommits everything in the range but keeps all changes in the
   working tree. Verify:
   ```bash
   git diff --stat   # should match step 3's total diff
   ```

8. **Commit each group** in plan order:
   ```bash
   # For file-level grouping:
   git add <file1> <file2>
   git commit -m "type(scope): description"

   # For hunk-level splitting within a file:
   git add -p <file>
   git commit -m "type(scope): description"
   ```

   After each commit, verify nothing was missed or double-counted:
   ```bash
   git diff --stat   # remaining uncommitted changes
   ```

   Each commit must:
   - Be describable in one sentence
   - Leave the codebase in a working state
   - Not mix concerns (if in doubt, split smaller)

9. **Verify the result**:
   ```bash
   git sl
   ```
   Show the user the new stack.

   Confirm the total diff is identical:
   ```bash
   git diff $BASE..HEAD --stat   # should match step 3
   ```

10. **Run tests** if a test command is identifiable:
    ```bash
    git test run -x '<test-command>' 'stack()'
    ```
    Report any commits that break the build.

## Tips

- **Don't lose changes.** After step 7, double-check `git diff --stat` matches
  the original range diff. If anything is missing, stop and investigate.
- Format-only changes (whitespace, import sorting) should ALWAYS be a separate
  commit — they dominate diffs and obscure real changes.
- If the total changeset is small enough to group by file (no hunk splitting
  needed), prefer `git add <files>` over `git add -p` for speed.
- If a commit is getting too large (>200 lines), split it further rather than
  letting it grow.
- Commit messages should explain WHY, not just WHAT.
- If the user wants to keep some of the original commit boundaries, respect
  that — not every restack needs to flatten everything.
