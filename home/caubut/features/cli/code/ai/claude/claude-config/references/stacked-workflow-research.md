# Stacked Workflow Research

Compiled 2026-03-21. Sources: git-branchless wiki, Graphite guides, Pragmatic
Engineer, Jackson Gabbard, Dr. Michaela Greiler, stacking.dev, and others.

---

## Part 1: git-branchless

### Design Goals

The git-branchless project serves as a natural half-step to Jujutsu (`jj`).

Design principles:
- **Support onboarding**: Incremental adoption. `git undo` works standalone.
- **Decrease complexity**: Remove incidental complexity (e.g., staging area).
- **Increase velocity**: Commits/branches easier to make and throw away.
- **Perform well**: Must scale to monorepo-sized repos, millisecond commands.

### Concepts

- **Working copy snapshots**: Ephemeral commits including unstaged changes. Used
  by `git undo`. Excludes untracked files. Auto-GC'd.
- **Main branch**: Single branch into which all commits merge/rebase.
- **Anonymous branching**: All "active" commits visible in smartlog without
  branches. Enables speculative work without branch overhead.
- **Commit stacks**: Series of commits forming a subtree of the DAG (not just
  linear). `git move` can move entire subtrees.
- **Speculative merges**: Never starts conflict resolution unless `-m`/`--merge`
  is passed. Operations tried in-memory first.
- **Bitemporality**: Per-branch timeline (git log) + per-commit timeline (how a
  commit changed over time). Powers `git undo`.

### Configuration

| Option | Default | Description |
|--------|---------|-------------|
| `branchless.core.mainBranch` | `master` | Main branch name |
| `branchless.revsets.alias.<key>` | — | Custom revset aliases |
| `branchless.smartlog.defaultRevset` | `((draft() \| branches() \| @) % main()) \| branches() \| @` | Default smartlog query |
| `branchless.commitMetadata.branches` | `true` | Show branches in smartlog |
| `branchless.commitMetadata.relativeTime` | `true` | Show relative timestamps |
| `branchless.restack.preserveTimestamps` | `false` | Preserve authored timestamps |
| `branchless.restack.warnAbandoned` | `true` | Warn on abandoned children |
| `branchless.next.interactive` | `false` | Default interactive for ambiguous nav |
| `branchless.undo.createSnapshots` | `true` | Create working copy snapshots |
| `branchless.navigation.autoSwitchBranches` | `true` | Auto-switch on target commits |

### Revsets

Names resolve via `git rev-parse`. `.` = `HEAD`.

**Functions:**
- `all()`, `none()`, `union(x, y)`, `intersection(x, y)`, `difference(x, y)`
- `only(x, y)`: ancestors of x but not ancestors of y
- `range(x, y)`: descendants of x AND ancestors of y
- `ancestors(x)`, `ancestors.nth(x, n)`, `descendants(x)`
- `parents(x)`, `parents.nth(x, n)`, `children(x)`
- `roots(x)`, `heads(x)`, `merges()`
- `main()`, `public()` (= `ancestors(main())`), `draft()`
- `stack([x])`: draft commits in stack containing x (default HEAD)
- `branches([pattern])`, `message(pattern)`, `paths.changed(pattern)`
- `author.name(p)`, `author.email(p)`, `author.date(p)`
- `committer.name(p)`, `committer.email(p)`, `committer.date(p)`
- `exactly(x, n)`: commits in x only if x has exactly n commits
- `current(x)`: resolve rewritten commits to current version
- `tests.passed([p])`, `tests.failed(...)`, `tests.fixable(...)`

**Operators:**
- `::x` = `ancestors(x)`, `x::` = `descendants(x)`
- `+`, `|`, `or` = union; `&`, `and` = intersection
- `-` = difference (use spaces: `foo - bar`)
- `%` = `only`; `::` (binary) = `range`; `..` = `only`

**Patterns:** `substr:`, `exact:`, `glob:`, `regex:`
**Dates:** `before:date`, `after:date`

**Aliases** via git config:
```ini
[branchless "revsets.alias"]
    grandChildren = children(children($1))
    sole = exactly($1, 1)
    onlyChild = sole(children($1))
    siblings = children(onlyParent($1)) - $1
```

### Commands

#### git smartlog (`git sl`)
Graphical commit graph focused on your commits. Icons: `◇` = public, `◯` =
draft, `✕` = hidden. Accepts revset: `git smartlog 'branches()'`.

#### git undo
Undo any commit graph operation. `-i`/`--interactive` for time-travel UI.
Can't undo: untracked file changes, staging (without snapshots).

#### git sw (`git branchless switch`)
Interactive fuzzy search and checkout. `git sw -i`, `git sw -i foo`.

#### git next / git prev
Navigate stacks. Options: `<N>` (count), `--oldest`/`--newest`/`--interactive`,
`-a`/`--all` (first/last), `-b`/`--branch`, `-ab` (first/last branch).

#### git record
Replace `git add` + `git commit`. Without staged changes: commits all unstaged.
`-i` = interactive TUI, `-c <name>` = create branch, `-d` = detach,
`-I` = insert into stack.

#### git amend
Amend current commit + auto-restack. Never updates message. `--reparent` to
amend without rebasing children.

#### git reword
Edit messages without checkout. `git reword <commit>`, `-m <msg>`,
`git reword 'stack()'` for batch.

#### git move
Move commits in graph. In-memory, handles subtrees, never starts conflicts
without `--merge`. Options: `-s`/`--source`, `-b`/`--base`, `-d`/`--dest`,
`-x`/`--exact`, `-I`/`--insert`, `-F`/`--fixup`.

#### git restack
Fix abandoned commits (parent rewritten, children point to old parent).

#### git hide / git unhide
Hide/show commits from smartlog. `-r` for recursive (subtree).

#### git split
Extract changes. Modes: default (insert after), `--detach` (sibling),
`--discard`, `--before` (insert before).

#### git test
Run commands on commit sets. `--exec '<cmd>'`, `--command <alias>`.
Strategies: `working-copy` (single), `worktree` (concurrent).
`--jobs N` (0 = auto CPUs, >1 implies worktree).
**Fix mode**: `git test fix --exec 'fmt'` — applies changes per commit, never
produces merge conflicts, can run in parallel.
**Search**: `--search linear|reverse|binary`, `-b`/`--bisect`.

#### git query
Revset queries. `-r`/`--raw` for script output. `--branches` for branch names.

#### git sync
Rebase all stacks onto main without checkout. `--pull` to fetch first.
Skips conflicts unless `--merge`.

#### git submit
Push branches to remote. Force-pushes existing. `-c`/`--create` for new.
`--forge phabricator` for Phabricator.

### Workflow: Divergent Development

1. Detach: `git checkout --detach`
2. Make speculative commits (don't need to build/pass tests)
3. Backtrack: `git prev 2`, make new commits (creates tree)
4. Clean up: `git hide -r <hash>` rejected approaches
5. Confirm: `git rebase -i main` with reword/fixup/squash
6. Create branch for push/PR

### Workflow: Editing Old Commits

1. **Amend directly**: `git checkout <hash>` → changes → `git commit --amend` → `git restack`
2. **Fixup child**: `git checkout <hash>` → changes → `git commit` → `git rebase -i main` (fixup) → `git restack`
3. **Commute upward**: changes on top → `git rebase -i main` → move line → `git restack`

---

## Part 2: git-absorb

Port of Facebook's `hg absorb`. Auto-maps staged changes to correct fixup commits.

### Usage

```bash
git add $FILES_YOU_FIXED
git absorb --and-rebase
```

### How It Works

Checks if patches commute. Examines commit range ending at HEAD (default: last
10, configurable via `absorb.maxStack`). Non-commuting commit = target.

### Flags

| Flag | Description |
|------|-------------|
| `-r, --and-rebase` | Auto-rebase after |
| `-n, --dry-run` | Preview |
| `--force-author` | Include other authors' commits |
| `-F, --one-fixup-per-commit` | Single fixup per target |
| `-s, --squash` | Squash commits instead of fixup |
| `-w, --whole-file` | Match files to first commit touching them |

### Configuration

```ini
[absorb]
    maxStack = 50
    oneFixupPerCommit = true
    autoStageIfNothingStaged = true
```

### Recovery

`git reset --soft PRE_ABSORB_HEAD`

---

## Part 3: git-revise

In-memory commit rewriting. All merges in-memory — never touches working
directory or index. Faster than rebase on large codebases.

### Options

| Option | Description |
|--------|-------------|
| `-a, --all` | Stage tracked file changes before revising |
| `-p, --patch` | Interactive hunk staging |
| `--no-index` | Ignore staged changes |
| `--reauthor` | Reset author |
| `-i, --interactive` | Edit todo list |
| `--autosquash` | Auto fixup!/squash! |
| `-c, --cut` | Interactive split |
| `-e, --edit` | Edit message |

### Interactive Commands

`index`, `pick`, `squash`, `fixup`, `reword`, `cut`

### Recovery

`git reset @{1}` — successful operation = one reflog entry.

---

## Part 4: Why Stacked Commits/PRs Matter

### Reviewability
- **400 lines** is the upper bound for effective review; ideal is **50-200 lines**.
- Analysis of 15M PRs: large PRs create review paralysis.
- Stacking forces authors to take the reviewer's perspective.

### CI Speed
- Smaller changes run CI faster and isolate failures.
- Per-commit CI (Meta's Sandcastle model).

### Merge Conflicts
- Smaller changes less likely to conflict.
- Single `git pull --rebase` from master resolves stacks vs cascading rebases.

### Developer Productivity
- Stacking parallelizes development and review — you're never blocked.
- Regular stackers create stacks of 5-10 PRs per feature.

---

## Part 5: Atomic Commit Best Practices

### The Three Tests

1. **Describable in one sentence** — if you need "and", split it.
2. **Independently revertable** — undo exactly one concern.
3. **Leaves codebase working** — tests pass, code compiles.

### Splitting Categories

- Database schema/queries (first)
- Business logic/services (second)
- UI/presentation (third)
- Or: scaffolding → core logic → edge cases → tests

### Sizing Heuristics

- Upper bound: 400 lines per reviewable unit
- Sweet spot: 50-200 lines
- Rule of thumb: one sentence description or split

---

## Part 6: How Companies Use Stacked Workflows

### Meta
- Engineers "live and breathe stacked diffs"
- Unit of change = individual commit ("diff"), not branch
- Phabricator for review, Sandcastle for CI, Landcastle for deploy
- Engineers work on master directly

### Google
- Gerrit: single commit per change, push to `refs/for/master`
- Iteration via `git commit --amend` (new "patch set" in same change)
- Review labels: +2 (approve), +1 (support), -1 (block), -2 (veto)

### Uber
- Phabricator-based stacked diffs
- Rebasing "almost a daily habit"

---

## Part 7: Anti-Patterns

- **Mixing refactoring with features** — refactor first, feature second, separate commits
- **"Addresses feedback" commits** — always fixup/absorb into original
- **Mega-commits** — format + functional changes mixed hides real changes
- **Raw dev history** — clean up before pushing (sausage-making philosophy)
- **Demanding unrelated refactoring in review** — abuse of reviewer authority

---

## Part 8: Retroactive Stack Splitting

### Technique 1: Interactive Rebase + Edit
1. `git rebase -i <commit>^`, mark `edit`
2. `git reset HEAD^` — unwind, keep changes
3. `git add -p` — stage hunks for first commit
4. `git commit`, repeat, `git rebase --continue`

### Technique 2: Soft Reset
1. `git reset --soft main` — uncommit all, keep staged
2. `git restore --staged .` — unstage to working tree
3. `git add -p` → `git commit`, repeat

### Technique 3: git-branchless split
`git split` with modes: insert after, `--detach`, `--discard`, `--before`

---

## Sources

- [git-branchless wiki](https://github.com/arxanas/git-branchless/wiki)
- [git-absorb](https://github.com/tummychow/git-absorb)
- [git-revise](https://github.com/mystor/git-revise)
- [stacking.dev](https://www.stacking.dev/)
- [Pragmatic Engineer: Stacked Diffs](https://newsletter.pragmaticengineer.com/p/stacked-diffs)
- [Pragmatic Engineer: Stacked Diffs at Meta](https://newsletter.pragmaticengineer.com/p/stacked-diffs-and-tooling-at-meta)
- [Jackson Gabbard: Stacked Diffs vs Pull Requests](https://jg.gg/2018/09/29/stacked-diffs-versus-pull-requests/)
- [Dr. Michaela Greiler: Stacked Pull Requests](https://www.michaelagreiler.com/stacked-pull-requests/)
- [Graphite guides](https://graphite.dev/guides)
- [Samuel Faure: Atomic Git Commits](https://dev.to/samuelfaure/how-atomic-git-commits-dramatically-increased-my-productivity-and-will-increase-yours-too-4a84)
- [Aleksandr Hovhannisyan: Atomic Git Commits](https://www.aleksandrhovhannisyan.com/blog/atomic-git-commits/)
- [Seth Robertson: Git Best Practices](https://sethrobertson.github.io/GitBestPractices/)
- [Simon Tatham: Code Review Antipatterns](https://www.chiark.greenend.org.uk/~sgtatham/quasiblog/code-review-antipatterns/)
