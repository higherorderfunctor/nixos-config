---
repo: arxanas/git-branchless
repo-head: f238c0993fea69700b56869b3ee9fd03178c6e32
repo-indexed: 2026-03-21
wiki-head: 98aa4029b230f432416e9029fe6182ed8fa1d695
wiki-indexed: 2026-03-21
issues-indexed: 2026-03-21
discussions-indexed: 2026-03-21
labels-indexed: 2026-03-21
label-head: 904c06c39a895525e0e94a1888d19139c20c7eedfb489ef889635d3ea5d45e30
exclude-issue-patterns:
  - "renovate"
  - "dependabot"
  - "bump version"
  - "release v"
value-labels:
  - name: "bug"
    reason: "confirmed bugs reveal edge cases and error handling details"
  - name: "has-workaround"
    reason: "direct workarounds and recipes for known issues"
  - name: "no-planned-fix"
    reason: "confirmed limitations users must work around"
  - name: "question"
    reason: "resolved Q&A with usage patterns and recipes"
  - name: "documentation"
    reason: "doc gaps and usage clarifications"
  - name: "enhancement"
    reason: "feature discussions and design decisions"
  - name: "good first issue"
    reason: "sometimes reveals architectural patterns"
  - name: "help wanted"
    reason: "community-discussed issues, often contain workarounds"
issue-stats:
  total-fetched: 1551
  from-labels: 248
  from-keywords: 166
  from-reactions: 1465
  after-dedup: 1456 issues + 95 discussions
---

# git-branchless Reference

Distilled from https://github.com/arxanas/git-branchless, updated 2026-03-21.

## Overview

git-branchless is a suite of Git extensions that adds anonymous branching,
in-memory rebases, commit graph visualization, and a general-purpose undo
system. It enables patch-stack workflows (as used at Meta, Google, and the
Linux project) where the unit of change is an individual commit rather than a
branch. All rewrite operations (move, sync, restack) run in-memory by default,
never touching the working copy unless merge conflicts require it.

The tool is fully compatible with branches — "branchless" refers to the ability
to work *without* them when convenient, via anonymous branching where all draft
commits stay visible in the smartlog.

**Status:** Alpha. Latest release v0.10.0 (Oct 2024). The maintainer considers
Jujutsu the long-term successor; git-branchless serves as a bridge and
workflow test-bed.

## Installation & Setup

```bash
# Nix (already in your overlay), or:
cargo install --locked git-branchless

# Initialize in each repository (idempotent)
git branchless init

# Set main branch if not auto-detected
git config branchless.core.mainBranch main
```

### Key Configuration

```bash
# Set default push remote for git submit --create
git config remote.pushDefault origin

# Interactive mode for git next when ambiguous
git config branchless.next.interactive true

# Preserve timestamps during restack
git config branchless.restack.preserveTimestamps true

# Test strategy and parallelism
git config branchless.test.strategy worktree
git config branchless.test.jobs 0

# Define test command aliases
git config branchless.test.alias.check "nix fmt -- --check"

# Revset aliases
git config 'branchless.revsets.alias.d' 'draft()'
```

### All Configuration Options

| Key | Default | Description |
|-----|---------|-------------|
| `branchless.core.mainBranch` | `master` | Main branch name |
| `branchless.next.interactive` | `false` | Interactive ambiguity resolution |
| `branchless.navigation.autoSwitchBranches` | `true` | Auto-switch to branch on target |
| `branchless.restack.preserveTimestamps` | `false` | Keep authored timestamp |
| `branchless.restack.warnAbandoned` | `true` | Warn about abandoned children |
| `branchless.smartlog.defaultRevset` | *(complex)* | Default smartlog query |
| `branchless.commitMetadata.branches` | `true` | Show branches in smartlog |
| `branchless.commitMetadata.relativeTime` | `true` | Show timestamps in smartlog |
| `branchless.undo.createSnapshots` | `true` | Working copy snapshots for undo |
| `branchless.test.strategy` | `working-copy` | Test isolation strategy |
| `branchless.test.jobs` | `1` | Parallel test jobs (0 = auto) |
| `branchless.test.alias.<name>` | — | Named test commands |
| `branchless.revsets.alias.<key>` | — | Custom revset aliases |

## Core Concepts

### Commit Stacks
A series (or subtree) of draft commits. Unlike branches, stacks can diverge
into multiple lines of work. Commands like `git move` operate on entire
subtrees, not just linear sequences.

### Public vs Draft Commits
- **Public**: on the main branch (diamond `◆`/`◇` in smartlog). Immutable.
- **Draft**: your local work, not yet on main (circle `◯`/`●`). Freely rewritable.

### Anonymous Branching
You can make commits in detached HEAD mode. They stay visible in the smartlog
without needing a branch name. Useful for speculative/experimental work.

### Speculative Merges
Operations like `git move` and `git sync` speculatively apply rebases
in-memory. If a merge conflict would occur, they abort cleanly without
starting conflict resolution (unless `--merge` is passed).

### Bitemporality
git-branchless tracks how commits change over time (like Mercurial's Changeset
Evolution). This powers `git undo` — you can undo any graph operation by
browsing previous states of the repository.

### Working Copy Snapshots
Some commands create ephemeral snapshots of the working copy (including
unstaged changes). These power `git undo` but never include untracked files.
Auto garbage-collected. Disable via `branchless.undo.createSnapshots = false`.

## Command Reference

### Visualization

**`git sl`** (smartlog) — Show your commit graph.
```bash
git sl                    # default: draft commits + branches
git sl 'stack()'          # only current stack
git sl 'branches()'       # only commits with branches
```

Icons: `◆`/`◇` = public, `◯`/`●` = draft (● = HEAD), `✕` = hidden/abandoned.

Visibility rules: shows checked-out commit, commits with branches, your
commits (not hidden), commits with visible descendants, and hidden public
commits that were rewritten. Commits made before `git branchless init`
won't appear. For color in pipes: `git branchless --color always smartlog`
(flag goes before subcommand, #1308).

### Navigation

**`git next`** / **`git prev`** — Move through the stack.
```bash
git next                  # move to child commit
git next 3                # move 3 commits forward
git next -a               # jump to end of stack (leaf)
git prev -a               # jump to start of stack (root)
git next -b               # jump to next branch
git prev -ab              # jump to first branch in stack
git next -n               # pick newest when ambiguous
git next -i               # interactive selection when ambiguous
```

**`git sw -i`** — Fuzzy interactive switch (powered by Skim).
```bash
git sw -i                 # open selector for all visible commits
git sw -i foo             # pre-filter with search term "foo"
```

### Committing

**`git record`** — Commit without staging.
```bash
git record -m "msg"       # commit all unstaged changes
git record -i             # interactive hunk selection (TUI)
git record -I             # insert commit into middle of stack
git record -c branch-name # create new branch and commit
git record -d             # detach from current branch first
```

Note: If changes are staged, `git record` uses only those. Otherwise it
commits all unstaged tracked changes. Untracked files still need `git add`.

**`git amend`** — Amend current commit + auto-restack descendants.
```bash
git amend                 # amend with all unstaged changes
git add file && git amend # amend with only staged changes
git amend --reparent      # amend without rebasing children (for formatters)
```
**Gotcha:** `git amend` skips pre-commit hooks (#1275). Use `git commit --amend` + `git restack` if hooks are needed.

### Rewriting

**`git reword`** — Edit commit messages without checkout.
```bash
git reword                         # edit HEAD message in $EDITOR
git reword <hash>                  # edit specific commit's message
git reword <hash> -m "new msg"     # replace message inline
git reword 'stack()'               # batch reword entire stack
```
**Gotcha:** `git reword` rewrites all stack commits even when only one message changed (#1385).

**`git move`** — Move commits/subtrees in the graph (in-memory rebase).
```bash
git move -s <src> -d <dest>   # move src + descendants onto dest
git move -b <branch> -d <dest> # move branch's entire lineage onto dest
git move -x <hash> -d <dest>  # move exact commit only (no descendants)
git move -d <dest>             # move current stack onto dest (default -b HEAD)
git move -s <src>              # move src onto HEAD (default -d HEAD)
git move -I                    # insert commit between others
git move -F -x <src> -d <dest> # fixup: combine src into dest
```

Defaults: no `-d` → `HEAD`; no `-s`/`-b` → `-b HEAD`.
Conflicts: fails cleanly unless `--merge` is passed.

**`git split`** — Extract changes from a commit.
```bash
git split                 # interactive: extract hunks into new child commit
git split --before        # extracted changes become parent of target
git split --detach        # extracted changes become sibling
git split --discard       # remove extracted changes entirely
```

**`git restack`** — Fix abandoned commits after rewrites.
```bash
git restack               # restack all abandoned commits
git restack <hash>        # restack only children of specific hidden commit
```

### Stack Management

**`git sync`** — Rebase all stacks onto updated main.
```bash
git sync                  # rebase all draft stacks (local only)
git sync --pull           # fetch remote first, then rebase
git sync 'stack()'        # rebase only current stack
git sync --merge          # resolve conflicts for all stacks
```

Conflict handling: skips conflicting stacks by default, prints summary.
Fix individually: `git move -b <hash> -d main --merge`.

**Gotcha:** `git sync --pull` with a dirty working tree can strand you on an old commit (#1137). Commit or stash first.
**Gotcha:** `git sync` in worktrees may corrupt the index in other worktrees (#1524). Check `git status` afterward.
**Gotcha:** Squash-merged PRs are not detected by `git sync` — manually `git hide -r <hash>` (#965).

**`git submit`** — Push branches to remote.
```bash
git submit                # force-push existing remote branches in stack
git submit -c             # create + push new remote branches
git submit @              # push only branches at HEAD
git submit 'draft()'      # push all draft branches
```

Note: force-pushes by design (updating review branches). Set
`git config remote.pushDefault origin` for `--create`.

**Gotcha:** `git submit` skips commits with 2+ branches attached (#1131). One branch per commit.

**Known issue:** GitHub forge (`--forge github`) requires two executions —
first creates PR with wrong base, second fixes it (#1550). Multiple bugs
with stack reorder (#1259). Prefer manual `gh pr create` workflow.

### Undo & Recovery

**`git undo`** — Undo any graph operation.
```bash
git undo                  # undo last operation
git undo -i               # interactive: browse repo states, pick one
```

Can undo: commits, amends, rebases, merges, checkouts, branch operations.
Cannot undo: working copy changes (unless captured in a snapshot), untracked
files. Requires Git v2.29+. Can undo a `git undo`.

**`git hide`** / **`git unhide`** — Remove commits from smartlog.
```bash
git hide <hash>           # hide single commit
git hide -r <hash>        # hide commit + all descendants
git unhide <hash>         # bring back a hidden commit
```

### Testing

**`git test run`** — Run a command across commits.
```bash
git test run -x 'nix fmt -- --check'          # test current stack
git test run -x 'make test' 'draft()'          # test all drafts
git test run -x 'cmd' --jobs 0                 # parallel (auto CPU count)
git test run -x 'cmd' --strategy worktree      # isolated worktrees
git test run -x 'cmd' --search binary          # bisect for first failure
git test run -x 'cmd' -b                       # shorthand for --bisect
git test run -c check                          # use command alias "check"
```

Results are cached by command + tree ID. Use `--no-cache` to bypass.
Environment: `BRANCHLESS_TEST_COMMIT`, `BRANCHLESS_TEST_COMMAND` available.

**`git test fix`** — Apply formatter/linter fixes to each commit.
```bash
git test fix -x 'cargo fmt --all'              # format each commit
git test fix -x 'cmd' --jobs 0                 # parallel fixing
```

`git test fix` never produces merge conflicts — it replaces each commit's
tree directly, leaving descendants unchanged.

**`git test show`** — Show previous test results.
```bash
git test show -x 'cmd'                         # pass/fail summary
git test show -x 'cmd' -v                      # with output
git test clean 'stack()'                       # clear cached results
```

### Querying

**`git query`** — Execute revset queries.
```bash
git query 'stack() & paths.changed(*.nix)'    # nix files in current stack
git query --branches 'draft() & branches()'    # branch names on drafts
git query -r 'stack()'                         # raw hashes for scripting
```

### Diff Tools

**`git branchless difftool`** — Interactive diff viewing (v0.8.0+).
```gitconfig
[difftool "branchless"]
  cmd = git-branchless difftool --read-only --dir-diff $LOCAL $REMOTE
[mergetool "branchless"]
  cmd = git-branchless difftool $LOCAL $REMOTE --base $BASE --output $MERGED
```

## Revset Quick Reference

### Functions
| Function | Description |
|----------|-------------|
| `stack([x])` | Draft commits in stack containing x (default: HEAD) |
| `draft()` | All draft (non-public) commits |
| `main()` | Tip of main branch |
| `public()` | All public commits (= `ancestors(main())`) |
| `branches([pat])` | Commits with branches (optionally matching pattern) |
| `all()` | All visible commits |
| `none()` | Empty set |
| `children(x)` / `parents(x)` | Immediate children/parents |
| `descendants(x)` / `ancestors(x)` | All descendants/ancestors (inclusive) |
| `ancestors.nth(x, n)` / `parents.nth(x, n)` | Nth ancestor/parent |
| `heads(x)` / `roots(x)` | Leaf/root commits within set |
| `merges()` | Merge commits |
| `message(pat)` | Commits matching message pattern |
| `paths.changed(pat)` | Commits touching matching file paths |
| `author.name(pat)` / `author.email(pat)` | Filter by author |
| `author.date(pat)` / `committer.date(pat)` | Filter by date |
| `current(x)` | Resolve rewritten commits to current version |
| `exactly(x, n)` | x only if it contains exactly n commits |
| `tests.passed([cmd])` / `tests.failed([cmd])` | Test result filters |
| `tests.fixable([cmd])` | Commits fixable by `git test fix` |

### Operators
| Operator | Meaning |
|----------|---------|
| `x + y`, `x \| y`, `x or y` | Union |
| `x & y`, `x and y` | Intersection |
| `x - y` | Difference (space required: `foo - bar`) |
| `x % y`, `x..y` | Only: ancestors of x NOT ancestors of y |
| `x:y`, `x::y` | Range: descendants of x AND ancestors of y |
| `:x`, `::x` | Ancestors of x |
| `x:`, `x::` | Descendants of x |

### Patterns (for text-matching functions)
- `foo`, `substr:foo` — substring match
- `exact:foo` — exact match
- `glob:foo/*` — glob match
- `regex:foo.*` — regex match
- `before:2024-01-01`, `after:1 month ago` — date patterns

### Aliases
```bash
# Define in git config
git config 'branchless.revsets.alias.d' 'draft()'
git config 'branchless.revsets.alias.onlyChild' 'exactly(children($1), 1)'

# Use anywhere
git query 'd()'
git sl 'onlyChild(HEAD)'
```

## Recipes

### 1. Start a new commit stack from main
```bash
git checkout main
git checkout --detach          # or: git record -d -m "first commit"
# make changes...
git record -m "feat(scope): first change"
# make more changes...
git record -m "feat(scope): second change"
git sl                         # verify stack looks right
```

### 2. Edit an old commit's contents
```bash
# Option A: checkout + amend (simplest)
git prev 2                     # navigate to target commit
# make changes...
git amend                      # amend + auto-restack descendants
git next -a                    # return to stack tip

# Option B: amend from anywhere with git-absorb
# make changes in working tree that fix a specific earlier commit
git add -p                     # stage the fix
git absorb --and-rebase        # auto-routes to correct commit

# Option C: make fix commit, then combine
git record -m "fixup! original message"
GIT_SEQUENCE_EDITOR=: git rebase --interactive --autosquash main
git restack                    # if branches were abandoned
```

### 3. Edit an old commit's message
```bash
git reword <hash> -m "feat(scope): better description"
# or open in editor:
git reword <hash>
# batch reword entire stack:
git reword 'stack()'
```

### 4. Reorder commits in a stack
```bash
# Move commit <hash> on top of HEAD (reorder it to after current position)
git move -x <hash> -d HEAD

# Move commit to a specific position
git move -x <hash> -d <target>
```

### 5. Move a commit stack to a new base
```bash
git move -d main               # move current stack onto main
git move -b feature -d main    # move feature's lineage onto main
```

### 6. Split a large commit
```bash
git checkout <hash>
git split                      # interactive: select hunks for new commit
# or with git rebase:
git rebase -i <hash>^          # mark commit as "edit"
git reset HEAD^                # unwind, keep changes in working tree
git add -p && git commit       # first logical group
git add -p && git commit       # second logical group
git rebase --continue
```

### 7. Squash commits together
```bash
# Combine src into dest
git move -F -x <src> -d <dest>

# Or use interactive rebase
git rebase -i main             # mark commits as fixup/squash
```

### 8. Sync all stacks with remote main
```bash
git sync --pull                # fetch + rebase all stacks
# If some stacks conflict:
git move -b <conflicting-root> -d main --merge   # resolve individually
```

### 9. Push a stack for review
```bash
# First time: create branches for each commit
git branch feat-part-1 <hash1>
git branch feat-part-2 <hash2>
git submit -c                  # push all new branches

# Subsequent updates after amending/restacking:
git submit                     # force-push all existing remote branches
```

### 10. Undo a bad rebase
```bash
git undo                       # undo last operation
# or browse history:
git undo -i                    # interactive state browser
```

### 11. Run tests across the entire stack
```bash
git test run -x 'make test'                    # serial, current stack
git test run -x 'make test' --jobs 0           # parallel
git test run -x 'make test' --search binary    # find first failing commit
```

### 12. Format all commits in a stack
```bash
git test fix -x 'nix fmt' --jobs 0
# No merge conflicts — each commit's tree is replaced directly
```

### 13. Speculative / divergent development
```bash
git checkout --detach
# try approach A...
git record -m "temp: approach A"
git prev                       # go back to before approach A
# try approach B...
git record -m "temp: approach B"
git sl                         # see both approaches as siblings
# decide on B, hide A:
git hide -r <approach-A-hash>
# clean up temp commits with interactive rebase
```

### 14. Find commits that touched specific files
```bash
git query 'stack() & paths.changed(*.nix)'
git query 'draft() & paths.changed(src/)'
```

### 15. Insert a commit in the middle of a stack
```bash
git prev 2                     # navigate to insertion point
# make changes...
git record -I -m "new middle commit"   # insert + restack children
```

### 16. Resolve "trying to rewrite N public commits"
```bash
git restack -f                 # force past the check
git restack 'draft()'          # target only drafts
```
Happens when main was force-pushed or commits unexpectedly became public (#988).

### 17. Clean up stale commits after squash-merge
```bash
git sync --pull                # auto-cleans linearly merged stacks
git hide -r <hash>             # manually hide squash-merged stacks
git hide "draft() & message('substr:WIP')"  # bulk hide by pattern
```
`git sync` only detects linear merges, not squash merges (#965, #977, #1218).

## Anti-Patterns

### Don't use `git stash`
Commit instead. Anonymous commits are first-class in branchless — they appear
in the smartlog and can't be forgotten. Use `git hide` to clean up later.

### Don't run `git rebase` for moves
Use `git move` instead — it's in-memory, handles subtrees, moves branches,
and won't start conflict resolution unexpectedly.

### Don't use `-s` with branch names
`-s` (source) moves the commit and descendants. A branch points to the *last*
commit, so `-s branch` only moves the tip. Use `-b` (base) to move the entire
lineage.

### Don't forget `git restack` after stock git amend
If you use `git commit --amend` instead of `git amend`, descendants are
abandoned. Run `git restack` to fix. Better: always use `git amend` which
auto-restacks.

### Don't ignore abandoned commit warnings
When branchless says "This operation abandoned N commits!", run `git restack`
(or `git undo` if it was a mistake). Don't leave the graph in a broken state.

### Don't resolve conflicts unless needed
`git move` and `git sync` skip conflicts by default. Only pass `--merge` when
you're ready to resolve. This lets you safely try operations without risk.

### Don't use `feature.manyFiles = true` without workaround
Git v2.40.0+ with `index.skipHash` (set by `feature.manyFiles`) causes
libgit2 crashes. Same crash with `--index-version 4` (#1363). Workaround:
`git config --local index.skipHash false`.

### Don't commit on `main`
Commits on `main` are treated as public — they vanish from draft smartlog
and can't be rewritten. Always detach first (`git checkout --detach`) (#860).

### Don't init in a worktree
`git branchless init` only works from the main worktree, not from
`git worktree add` worktrees (#540).

### GPG/SSH signing not supported
git-branchless cannot sign commits. All rewrite operations produce unsigned
commits. This is a known limitation (issue #465, labeled "help wanted").
Community PR #1538 pending.

## Known Bugs

- **"Could not parse reference-transaction-line"** — harmless ERROR log on
  newer Git versions. Operations complete normally (#1388, #1321).
- **Git v2.46+ test failures** — reference-transaction hook changes break
  some tests; user impact unclear (#1416).
- **`git sync` slow on `main`** — redundant checkout per stack. Detach
  first to avoid (#1155).
- **Anti-GC ref accumulation** — 100k+ refs under `refs/branchless/*` over
  months. `git branchless gc` partially helps (#1125).
- **Rust 1.89+ build failure** — fails to compile with newer Rust (#1585).

## Integration

### With git-absorb
Routes staged fixup changes to the correct commit in the stack automatically.
```bash
git add -p                     # stage the fix
git absorb --and-rebase        # finds target commit, creates fixup, rebases
```
Set `git config absorb.maxStack 50` for deeper stacks.

### With git-revise
In-memory commit rewriting (alternative to rebase for some operations).
```bash
git revise -i                  # interactive rebase alternative
git revise -c <hash>           # split a commit interactively
git revise --autosquash        # process fixup! commits
```

**Caveat:** git-revise does not call `post-rewrite` hooks, so branchless
can't track the rewrite. Run `git restack` afterward. For operations where
branchless has equivalents (`reword`, `split`, `move`), prefer those.

### With GitHub (git submit workflow)
1. Create branches: `git branch feat-1 <hash>` for each commit
2. Push: `git submit -c` (creates remote branches)
3. Create PRs via `gh pr create --base <prev-branch> --head <branch>`
4. After amend/restack: `git submit` to force-push updates
5. After merge: `git sync --pull` auto-cleans merged commits

Set PR base to the previous branch in the stack; GitHub auto-updates
dependent PRs on merge (#716).

### Hooks Requirement
Hooks installed by `git branchless init` are required for commit tracking,
undo, and auto-restack. Without them, `git move` still works for basic
rebasing but loses commit tracking (#1286).

### Git Version Compatibility
- **v2.29+**: Full support including `git undo`
- **v2.24-2.27**: Supported, no `git undo`
- **v2.28**: Not supported (reference-transaction bug)
- **v2.46+**: Some test failures (#1416)
- **<= v2.23**: Not supported

<!-- BEGIN LOCAL NOTES — preserved across regeneration -->
## Local Notes

Hard-won lessons, workarounds, and patterns discovered through actual usage.
This section is never overwritten by index-repo-docs.

### `git amend --reparent` does not skip restacking

Despite the name suggesting it only re-parents, `--reparent` still restacks
all descendants — it just preserves their tree contents unchanged (no merge).
This means it's useful when the amended commit only changes metadata or
formatting (the descendant diffs stay the same), but it will **not** help
avoid conflicts when the amendment changes file content that descendants also
touch. For content-changing amends, use plain `git amend` and resolve
conflicts normally.

### Mid-stack reorganization commits cause conflict cascades

When a commit in the middle of a stack substantially rewrites a file (e.g.,
reordering sections, restructuring an attrset), any edit to that same file in
an earlier commit will conflict at the reorganization commit during restack —
and potentially at every descendant after it.

**Strategies:**
1. **Batch pre-reorganization edits** — make all changes to the file *before*
   the reorganization commit so the reorg sees a stable input.
2. **Edit the reorganization commit directly** — use `git amend` while checked
   out at that commit, so descendants rebase on top of the already-reorganized
   version.
3. **Accept one conflict** — if the reorganization empties or replaces a
   structure (e.g., clearing an attrset so each later commit adds one entry),
   expect exactly one conflict at the first descendant after the empty. All
   subsequent commits restack cleanly since they only add, never modify.

### Forward references in shell globs are silent failures

A shell glob like `${self}/apps/*.sh` in a nix `runCommand` or linter config
will silently expand to nothing when `apps/` doesn't exist yet. This won't
fail the build, but it's still a forward reference — the check isn't doing
anything until a later commit creates the directory. Defer the glob-based
check to the commit that introduces the directory it references.

### In-memory restack falls back to on-disk rebase on conflict

When `git amend` triggers an in-memory restack that hits a merge conflict, it
aborts the in-memory attempt and prints: "To resolve merge conflicts, run:
git restack --merge". Running `git restack --merge` then starts an on-disk
rebase that stops at each conflicting commit for manual resolution (`git add`
+ `git rebase --continue`). This is the normal flow, not an error state.

### `git rerere` has limited effectiveness across repeated restacks

`git rerere` records conflict resolutions during restack, but each amend to an
earlier commit changes the conflict context slightly. `rerere` auto-resolves
when the conflict is byte-identical to a previous one, but fails for
similar-but-not-identical conflicts (e.g., same file section but with a
one-line difference from the previous amend). Don't rely on it to eliminate
repeated conflict resolution when making multiple edits to the same file
across the stack.

### Removing content from early commits can orphan additions downstream

If you remove content (e.g., an attrset block, shell checks) from an early
commit and a later commit's restack conflicts, the conflict resolution may
drop the removed content from the "ours" side — but if the later commit was
*adding* to that block, the additions vanish too. After any restack with
conflict resolution, verify that content removed from an early commit was
re-added at the correct later commit. Use `git diff <backup>..HEAD` to
confirm the final tree is equivalent.

### `git move -x` does not move descendants

`-x` means "exact commit only." When moving a parent commit with `-x`, child
commits stay on the old branch and need separate `git move` commands. This is
easy to miss when moving a commit that has one obvious child (e.g., TODO →
flake.lock). Use `-s` to move a commit and all descendants, or `-b` to move
an entire branch lineage. When intentionally splitting parent from children,
do the parent first, then move each child to the new location.

### Branch pointers follow rewrites silently

When `git move` rewrites a commit, any branch pointing at the old commit
moves to the new one. This defeats backup branches: if
`backup/pre-operation` points at commit `abc123` and `git move` rewrites it
to `def456`, the branch now points at `def456` — the "before" state is lost.

**Workaround:** After any move/rebase that touches backup targets, immediately
`git branch -f backup/name <original-SHA>` to pin it back. The original SHA
survives in the object store; only the branch ref moved. Alternatively, use
`git tag` instead of `git branch` for bookmarks — tags are not updated by
rewrite operations.

### `git move -s` past a reorganization commit: expect per-commit conflicts

`git move -s <subtree> -d <target> --merge` with a reorganization commit in
the subtree falls back to on-disk rebase and stops at **each** conflicting
commit for manual resolution via `git rebase --continue`. Budget for one
conflict resolution per commit that touches the same files the reorganization
rewrites. The reorganization commit itself is the worst; descendants that only
add content (one table row, one attrset entry) are quick to resolve since the
pattern is always "take HEAD + add the incoming addition."

### In-memory amend succeeds when descendants don't touch the same files

When amending a commit to add content to files that no descendant touches
(e.g., adding ci.yml entries when no server commit modifies ci.yml), the
in-memory restack succeeds instantly for all descendants — no conflicts, no
on-disk fallback. This is the ideal case: structure your stack so shared
infrastructure files are introduced once and only modified by their own
commit, with server commits touching only their own overlay/module files.

### Alphabetical insertion via sed causes ordering drift

Using `sed -i '/<prev>/a\<new>'` to insert entries alphabetically works when
building a list from scratch, but breaks if a pre-existing entry is already in
the list (e.g., nixos-mcp inserted first by skeleton, then context7 through
sympy inserted alphabetically around it). The pre-existing entry drifts to the
wrong position because subsequent insertions reference their alphabetical
predecessor, not accounting for the pre-existing entry's position. Fix by
reordering in the last commit that completes the list, or by inserting the
first entry at a sentinel position that sorts correctly.

<!-- END LOCAL NOTES -->
