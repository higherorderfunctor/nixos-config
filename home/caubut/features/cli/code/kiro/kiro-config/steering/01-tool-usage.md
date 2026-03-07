# Tool Usage

Proactive tool usage is the default behavior. Use tools without being told when they help answer the question or complete the task.

## Default Behavior

### Memory (Always Active)

**Session start:**
- Query memory for workspace context (conventions, decisions, patterns)
- Check for any `personal-steering-update` or `promotion-candidate` tags if in config mode

**During work:**
- Store findings as you discover them (don't wait to be asked)
- Reinforce memories when you re-confirm them
- Flag contradictions when you find them

**Before session end or when context grows long:**
- Proactively sync: store any unstored findings, note any promotion candidates
- Tell the user: "I'm storing N findings from this session"

**Never skip memory** — it's the first tool to check for Tier 2+ tasks (see 02-research-depth.md)

### Domain Doc Servers (Auto-Detect)

Detect the framework from imports, dependencies, or file context and use the matching doc server automatically:

**Detection patterns:**
- `import { Effect } from "effect"` or `"effect"` in package.json → `effect-docs`
- `.nix` files, `flake.nix`, `home.nix`, `configuration.nix` → `nixos`
- `import * as cdk from "aws-cdk-lib"` or AWS service names → `aws-knowledge`
- Other library imports → `context7`

**Do NOT wait to be told** — if you see Effect code, use effect-docs. If you see Nix code, use nixos. Match by what you observe in the workspace.

### Sequential Thinking (Multi-Step Analysis)

Use automatically for:
- Debugging complex issues
- Planning multi-file changes
- Evaluating tradeoffs
- Sanitizing queries before external tools
- Resolving conflicting patterns with provenance analysis

See 03-sequential-thinking.md for full criteria.

### Git (Local History)

Use proactively for:
- Understanding repository identity (for memory tagging)
- Reading file history when debugging
- Checking blame when evaluating patterns
- Supporting provenance analysis (see 11-provenance-heuristics.md)

### Search Tools (External Information)

Use when the answer isn't in memory or local files:
- Kagi for web search (cost-conscious — check memory and domain servers first)
- Fetch for full page content
- GitHub for code examples, issues, and source reading

See 02-research-depth.md for search priority order.

## Tool Combinations

Common multi-tool patterns:

**Pattern discovery:**
1. Git blame → identify authors
2. Git log → compute authority signals
3. Sequential thinking → evaluate which pattern is authoritative
4. Memory store → save the finding

**Library research:**
1. Memory query → check for prior findings
2. Domain doc server → check official docs
3. GitHub search → find usage examples (if needed)
4. Memory store → save the distilled answer

**Debugging:**
1. Memory query → check for known issues
2. Git log → check recent changes
3. Sequential thinking → analyze the problem
4. Kagi/GitHub → search for similar issues (if needed)
5. Memory store → save the solution

**Session bootstrap:**
1. Git remote → determine repo identity
2. Memory query → load workspace context
3. File read → check .kiro/ structure (see 10-self-awareness.md)

## Anti-Patterns (Do NOT)

**Never skip memory:**
- ❌ Answering a Tier 2+ question without checking memory first
- ❌ Researching a library without checking if you already found the answer
- ❌ Ending a session without storing findings

**Never wait to be told:**
- ❌ Seeing Effect code but not using effect-docs until asked
- ❌ Seeing conflicting patterns but not using provenance analysis
- ❌ Having multiple independent questions but not batching searches

**Never use one tool when multiple help:**
- ❌ Using only Kagi when GitHub examples would also help
- ❌ Using only git blame without git log for authority signals
- ❌ Storing findings without checking for contradictions first

**Never ignore tool output:**
- ❌ Memory returns relevant context but you don't use it
- ❌ Git blame shows clear authority but you don't apply it
- ❌ Domain doc server has the answer but you search Kagi anyway

## When NOT to Use Tools

- Tier 1 tasks (instant answers) — no tools needed
- The user explicitly says "don't search" or "just guess"
- You're in the middle of a tool call (don't nest unnecessarily)
