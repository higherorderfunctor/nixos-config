---
repo: tummychow/git-absorb
last-indexed: 2026-03-21
repo-head: debdcd28d9db2ac6b36205bda307b6693a6a91e7
wiki-head: null
exclude-issue-patterns:
  - "renovate"
  - "dependabot"
  - "bump version"
  - "release v"
---

# git-absorb Reference

Distilled from https://github.com/tummychow/git-absorb, updated 2026-03-21.

## Overview

git-absorb is a port of Facebook's `hg absorb` for Mercurial. It automatically
folds staged changes into the correct ancestor commits by analyzing whether
patches "commute" (apply identically regardless of order). It examines a range
of recent commits (default: 10), identifies which ones modified the staged
lines, and creates `fixup!` commits accordingly.

The key insight: if a staged hunk modifies lines that were last touched by
exactly one ancestor commit, that hunk can be unambiguously attributed to that
commit. git-absorb creates fixup commits for each such match.

## Installation & Setup

Available in nixpkgs, Homebrew, Arch, Debian, Fedora, and others. From source:
`cargo install git-absorb`.

### Recommended Configuration

```bash
# Increase stack depth for branchless workflows (default: 10)
git config absorb.maxStack 50

# One fixup per commit (cleaner history)
git config absorb.oneFixupPerCommit true

# Auto-stage tracked changes if nothing staged
git config absorb.autoStageIfNothingStaged true

# Always reference targets by SHA (stable across rewording)
git config absorb.fixupTargetAlwaysSHA true
```

## Core Concepts

### Patch Commutation

git-absorb checks whether a staged hunk can be unambiguously attributed to a
single ancestor commit. If the lines modified in the hunk were last touched by
exactly one commit in the stack, the hunk "commutes" to that commit. If
multiple commits touched those lines, git-absorb skips the hunk (it's
ambiguous).

### Fixup Commits

git-absorb creates `fixup!` commits (or `squash!` with `--squash`). These are
consumed by `git rebase --autosquash` to fold into their targets. The
`--and-rebase` flag runs the rebase automatically.

### Stack Depth

By default, only the last 10 commits are candidates. Set `absorb.maxStack=50`
for deeper stacks. Use `--no-limit` to consider all commits until root, a
merge, or a different author. Use `--base <commit>` for explicit targeting.

## Command Reference

```
git absorb [FLAGS] [OPTIONS]
```

### Flags

| Flag | Description |
|------|-------------|
| `-r, --and-rebase` | Run autosquash rebase after creating fixups |
| `-n, --dry-run` | Show what would happen without making changes |
| `-F, --one-fixup-per-commit` | Consolidate to one fixup per target commit |
| `-s, --squash` | Create squash commits (edit message) instead of fixup |
| `-w, --whole-file` | Match first commit touching same file (not line-level) |
| `-f, --force` | Skip all safety checks |
| `--force-author` | Create fixups for other authors' commits |
| `--force-detach` | Allow on detached HEAD |
| `--no-limit` | Remove stack depth limit |
| `-v, --verbose` | Display more output |

### Options

| Option | Description |
|--------|-------------|
| `-b, --base <commit>` | Explicit base commit for absorb range |
| `-m, --message <msg>` | Body text for all generated fixup commits |
| `-- <REBASE_OPTIONS>` | Pass-through options for `git rebase` (must be last) |

### Configuration (`[absorb]` in .gitconfig)

| Key | Default | Description |
|-----|---------|-------------|
| `maxStack` | 10 | Number of ancestor commits to consider |
| `oneFixupPerCommit` | false | One fixup per target commit |
| `autoStageIfNothingStaged` | false | Auto-stage tracked changes if nothing staged |
| `fixupTargetAlwaysSHA` | false | Reference targets by SHA, not message |
| `forceAuthor` | false | Allow fixups to other authors' commits |
| `forceDetach` | false | Allow on detached HEAD |
| `createSquashCommits` | false | Create squash commits instead of fixup |

## Recipes

### 1. Fix a bug in an earlier stack commit

```bash
# Edit the file with the fix
vim src/broken.rs
# Stage only the fix
git add -p
# Create fixup and rebase in one step
git absorb --and-rebase
```

### 2. Bulk fixes across multiple stack commits

```bash
# Make all your fixes across multiple files
# Stage everything
git add -A
# Absorb routes each hunk to the correct commit
git absorb --and-rebase
```

### 3. Preview what absorb would do

```bash
git add -p
git absorb --dry-run
# If satisfied:
git absorb --and-rebase
```

### 4. Handle leftover staged changes

```bash
git add -A
git absorb --and-rebase
# Check if anything remains staged (absorb couldn't find a target)
git status
# Manually create a fixup for leftovers
git commit --fixup=<target-hash>
GIT_SEQUENCE_EDITOR=: git rebase -i --autosquash main
```

### 5. Absorb into a deep stack

```bash
# Temporarily increase depth
git absorb --and-rebase --base main

# Or configure permanently
git config absorb.maxStack 50
git absorb --and-rebase
```

### 6. Recover from a bad absorb

```bash
# Undo everything absorb did
git reset --soft PRE_ABSORB_HEAD
```

### 7. Absorb with auto-staging

```bash
# With config: absorb.autoStageIfNothingStaged = true
# Don't stage anything — absorb stages tracked changes, creates fixups,
# then unstages whatever it couldn't absorb
git absorb --and-rebase
```

## Anti-Patterns

### Don't use `--force` as a default

`--force` skips all safety checks (author, detach). Use `--force-author` or
`--force-detach` for specific overrides.

### Don't expect hook support

git-absorb uses libgit2 for commits, which does **not** run pre-commit hooks.
If your workflow requires hooks, run them manually after absorb:
```bash
git absorb --and-rebase
pre-commit run --from-ref HEAD~5 --to-ref HEAD  # if using pre-commit framework
```

### Don't rely on `includeIf` gitconfig

libgit2 doesn't fully support `includeIf` directives. If you use conditional
includes (e.g., for work email), put overrides in `.git/config` instead.

### Don't expect signed commits

`commit.gpgsign` is not honored. Fixup commits will be unsigned. This is a
libgit2 limitation with no current workaround.

### Don't absorb through merge commits

git-absorb only works with linear history. Merge commits in the stack will
cause errors or unexpected behavior.

## Integration

### With git-branchless

The primary workflow for stacked commits:
```bash
# Make fixes to code in the stack
git add -p
git absorb --and-rebase
# If branchless shows abandoned commits:
git restack
```

Configure `absorb.maxStack=50` to match typical branchless stack depths.

### With git-revise

Alternative to `--and-rebase`:
```bash
git absorb                    # create fixup commits only
git revise --autosquash       # in-memory autosquash (faster than rebase)
```

### Recovery

After any absorb operation, `PRE_ABSORB_HEAD` points to the pre-absorb state:
```bash
git reset --soft PRE_ABSORB_HEAD   # undo absorb completely
git diff PRE_ABSORB_HEAD           # inspect what changed
```
