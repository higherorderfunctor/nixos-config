---
name: stack-fix
description: Absorb staged changes into the correct commits in the current stack
argument-hint: "[--dry-run]"
---

Absorb code review feedback or fixes into the correct commits in the stack.
This routes each hunk to the commit it logically belongs to.

## Steps

1. **Check branchless init**:
   ```bash
   if [ ! -d ".git/branchless" ]; then git branchless init; fi
   ```

2. **Check for staged changes**:
   ```bash
   git diff --cached --stat
   ```
   If nothing is staged, check for unstaged changes and ask the user what to
   stage. Suggest `git add -p` for selective staging.

3. **Preview absorption** (dry run first):
   ```bash
   git absorb --dry-run
   ```
   Show the user which hunks will be absorbed into which commits. If any hunks
   can't be absorbed (they commute with all commits), warn that those will
   remain staged.

4. **Confirm with the user** that the mapping looks correct. If `$ARGUMENTS`
   contains `--dry-run`, stop here.

5. **Absorb and rebase**:
   ```bash
   git absorb --and-rebase
   ```

6. **Verify the result** with `git sl` to show the updated stack.

7. **Check for leftover changes**:
   ```bash
   git diff --cached --stat
   git diff --stat
   ```
   If hunks remain (couldn't be absorbed), inform the user and suggest:
   - Manually amending into a specific commit: `git prev` to navigate,
     `git amend`, then `git next -a`
   - Or creating a new commit if the changes are genuinely new work

8. **Run tests** if a test command is readily identifiable:
   ```bash
   git test run -x '<test-command>' 'stack()'
   ```
   Report any regressions introduced by the absorption.
