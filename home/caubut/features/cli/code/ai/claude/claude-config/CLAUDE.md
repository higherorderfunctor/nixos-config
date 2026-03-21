# Global Claude Code Instructions

## Config Management

All files under `~/.claude/` are managed via NixOS home-manager using
outOfStoreSymlinks. **Never write directly to `~/.claude/`**. Instead, edit the
source files in this repo at:

```
home/<user>/features/cli/code/ai/claude/claude-config/
```

Changes are live immediately (no rebuild needed) because they are symlinked.
If a new file or directory needs to be added to `~/.claude/`, update the nix
module at `home/<user>/features/cli/code/ai/claude/default.nix` to add the
symlink, then rebuild.

---

## Git Workflow: Stacked Commits with git-branchless

### Philosophy

Work in small, atomic commits. Every commit should:
- Be describable in one sentence (if you need "and", split it)
- Be independently revertable without side effects
- Leave the codebase in a working state (tests pass, code compiles)
- Target 50-200 lines of changed code

Never accumulate a large diff then commit at the end. Commit as you go, one
concern per commit. This is how Meta, Google, and Uber engineers work — the
unit of change is an individual commit, not a branch.

### Commit Ordering

When building a feature, structure the stack as:
1. Refactoring/cleanup (separate from feature work, always first)
2. Scaffolding / types / interfaces
3. Core business logic
4. Edge cases / error handling
5. Tests

Each of these is one or more separate commits. Never mix refactoring with
feature work in the same commit.

### History Hygiene

The commit history should read as a clean narrative — what *should* happen, not
a diary of what *did* happen during development.

- Never create "addresses feedback", "fix", "WIP", or "tweaks" commits
- Use `git absorb --and-rebase` to route fixes to the correct stack commit
- Use `git amend` to update the current commit (auto-restacks descendants)
- Use `git reword` to fix commit messages without checkout
- Clean up before pushing, not after

### Initialization

Before using any branchless commands in a repo, check if it's initialized:

```bash
# Check for branchless initialization
if [ ! -d ".git/branchless" ]; then
  git branchless init
fi
```

Always run this check before the first branchless command in a session.

### Command Preferences

Prefer git-branchless commands over stock git equivalents:

| Instead of | Use | Why |
|------------|-----|-----|
| `git log --graph` | `git sl` | Focused on your commits, cleaner output |
| `git rebase` | `git move` | In-memory, handles subtrees, no conflicts unless `--merge` |
| `git add` + `git commit` | `git record` | Skips staging, `-i` for interactive |
| `git commit --amend` | `git amend` | Auto-restacks descendants |
| `git rebase -i` (for messages) | `git reword` | No checkout needed, batch support |
| `git pull` + rebase | `git sync --pull` | Rebases all stacks, skips conflicts |
| `git push` (multiple branches) | `git submit` | Pushes entire stack at once |
| `git checkout` / `git switch` | `git sw -i` | Fuzzy search |
| `git log` (navigation) | `git next` / `git prev` | Stack-aware navigation |
| `git stash` | Just commit | Anonymous commits are first-class in branchless |

### Key Commands Reference

**Navigation:**
- `git sl` — smartlog (commit graph visualization)
- `git next` / `git prev` — move through stack (`-a` for all, `-b` for branch)
- `git sw -i` — fuzzy interactive switch

**Committing:**
- `git record -m "msg"` — commit without staging
- `git record -i` — interactive hunk selection
- `git record -I` — insert into middle of stack
- `git amend` — amend current commit + restack

**Rewriting:**
- `git reword <commit>` — edit message (no checkout)
- `git reword 'stack()'` — batch reword entire stack
- `git move -s <src> -d <dest>` — move commits/subtrees
- `git move -x <commit> -d <dest>` — move exact commits only
- `git split` — extract changes from a commit
- `git restack` — fix abandoned commits after rewrites

**Stack Management:**
- `git sync --pull` — rebase all stacks onto updated main
- `git submit -c` — push all branches in stack (create new)
- `git hide -r <hash>` — hide rejected work
- `git undo` — undo any graph operation (`-i` for interactive)

**Testing:**
- `git test run -x '<cmd>'` — run command across stack
- `git test run -x '<cmd>' --jobs 0` — parallel across commits
- `git test fix -x '<fmt>'` — apply formatter to each commit
- `git test run -x '<cmd>' --search binary` — bisect for failures

**Querying:**
- `git query 'stack() & paths.changed(*.ts)'` — find commits by criteria
- `git query --branches 'draft()'` — list branch names

### Revset Quick Reference

Use revsets for targeting commits in commands:
- `stack()` — current stack
- `draft()` — all draft (non-public) commits
- `main()` — tip of main branch
- `branches()` — all commits with branches
- `children(x)` / `parents(x)` — graph traversal
- `paths.changed(pattern)` — commits touching files
- `message(pattern)` — commits matching message
- `x::y` — range (descendants of x AND ancestors of y)
- `x % y` — only (ancestors of x NOT ancestors of y)

### Complementary Tools

**git-absorb**: Automatically routes staged changes to the correct fixup commit
in the stack by checking if patches commute. Use `git absorb --and-rebase` for
the common case. Configure `absorb.maxStack = 50` for deeper stacks.

**git-revise**: In-memory commit rewriting (never touches working directory).
Use `git revise -i` for interactive rebase alternative, `git revise -c <commit>`
to split a commit interactively, `git revise --autosquash` to process fixup commits.

### Breaking Up Large Commits

When splitting an existing large commit into a reviewable stack:

1. `git rebase -i <commit>^` — mark the commit as `edit`
2. `git reset HEAD^` — unwind commit, keep changes in working tree
3. `git add -p` — stage hunks for first logical group
4. `git commit -m "descriptive message"`
5. Repeat steps 3-4 for each logical group
6. `git rebase --continue` — replay remaining commits

Or use `git split` from branchless for simpler cases.

Alternative for full-stack restructure:
1. `git reset --soft main` — uncommit everything, keep staged
2. `git restore --staged .` — unstage to working tree
3. `git add -p` → `git commit`, repeat per concern
