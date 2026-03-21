---
name: stack-split
description: Break a large commit into a reviewable stack of small atomic commits
argument-hint: "[commit]"
---

Split a large commit into multiple smaller, atomic commits. Target commit
defaults to HEAD if not specified.

## Steps

1. **Check branchless init**:
   ```bash
   if [ ! -d ".git/branchless" ]; then git branchless init; fi
   ```

2. **Identify the target commit**. If `$ARGUMENTS` is provided, use it.
   Otherwise default to HEAD.

3. **Analyze the commit** to understand what it contains:
   ```bash
   git show --stat <commit>
   git show <commit>
   ```
   Read the full diff. Identify logical groups:
   - Refactoring / cleanup (should be first)
   - Type definitions / interfaces / schemas
   - Core logic changes
   - Edge cases / error handling
   - Tests
   - Config / build changes

4. **Propose a split plan** to the user. For each proposed commit:
   - One-sentence description
   - Which files/hunks belong to it
   - Why it's a separate concern

   Wait for user approval before proceeding.

5. **Perform the split** using interactive rebase:
   ```bash
   git rebase -i <commit>^
   ```
   Mark the target commit as `edit`, then:
   ```bash
   git reset HEAD^
   ```
   This unwinds the commit but keeps all changes in the working tree.

6. **Stage and commit each group** in the agreed order:
   ```bash
   git add -p  # or git add <specific-files>
   git commit -m "descriptive message for this group"
   ```
   Repeat for each logical group. Each commit must:
   - Be describable in one sentence
   - Leave the codebase in a working state
   - Target 50-200 lines

7. **Complete the rebase**:
   ```bash
   git rebase --continue
   ```

8. **Restack** if there are downstream commits:
   ```bash
   git restack
   ```

9. **Verify** the result:
   ```bash
   git sl
   ```
   Show the user the new stack. If a test command is available, run tests
   across the new commits:
   ```bash
   git test run -x '<test-command>' 'stack()'
   ```

## Alternative: Full Stack Restructure

If the user wants to restructure multiple commits (not just split one):

1. `git reset --soft main` — uncommit everything, keep changes
2. `git restore --staged .` — unstage to working tree
3. Stage and commit each logical group with `git add -p`
4. Verify with `git sl` and tests

## Tips

- Format changes should ALWAYS be a separate commit (they dominate diffs and
  hide functional changes)
- If a file has both refactoring and new logic, use `git add -p` to split
  hunks within the file
- Prefer too many small commits over too few large ones — they can always be
  squashed later
- Each commit message should explain WHY, not just WHAT
