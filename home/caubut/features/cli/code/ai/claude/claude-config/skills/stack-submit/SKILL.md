---
name: stack-submit
description: Sync stack with main, run tests, and submit all branches to remote
argument-hint: "[revset]"
---

Submit the current commit stack for review. If an argument is provided, use it
as a revset to select which commits to submit. Default is the current stack.

## Steps

1. **Check branchless init**:
   ```bash
   if [ ! -d ".git/branchless" ]; then git branchless init; fi
   ```

2. **Visualize the stack** with `git sl` to understand what will be submitted.

3. **Sync with main** to ensure the stack is up to date:
   ```bash
   git sync --pull
   ```
   If conflicts are reported (without `--merge`), stop and inform the user which
   commits conflict. Ask if they want to resolve with `git sync --merge` or
   handle individually with `git move -b <hash> -d main --merge`.

4. **Run tests across the stack** to validate each commit independently:
   ```bash
   git test run -x '<test-command>' 'stack()'
   ```
   Determine the test command from the project (package.json scripts, Makefile,
   Cargo.toml, etc.). If no obvious test command exists, ask the user.

   If any commit fails, stop and report which commit(s) failed. Do not submit
   a stack with failing tests.

5. **Verify commit messages** — review `git sl` output. Flag any commits with
   vague messages ("fix", "WIP", "update") and suggest rewording with
   `git reword <commit>`.

6. **Ensure branches exist** on each commit in the stack. If any commits lack
   branches, ask the user for branch names or suggest names based on commit
   messages.

7. **Submit**:
   ```bash
   git submit -c $ARGUMENTS
   ```
   If no argument was given: `git submit -c 'stack()'`

8. **Report results** — show which branches were pushed and any PR URLs if
   the forge integration provides them.
