---
name: Evolve global CLAUDE.md from workflow corrections
description: When user corrects stacked workflow usage in any repo, evaluate whether to update the global CLAUDE.md source in this repo
type: feedback
---

When the user corrects or reminds me about stacked workflow behavior (git-branchless, commit hygiene, stack skills, etc.) in ANY repo, consider whether the correction reveals a gap or inaccuracy in the global CLAUDE.md instructions.

**Why:** The stacked workflow instructions are new and will have nuances that only surface through real usage. The user wants a feedback loop where corrections get codified rather than repeated.

**How to apply:**
1. When corrected on workflow behavior, ask: "Is this something the CLAUDE.md instructions caused me to get wrong, or failed to prevent?"
2. If yes — propose a specific edit to the source file at `home/<user>/features/cli/code/ai/claude/claude-config/CLAUDE.md` in the nixos-config repo. The edit should be minimal and targeted.
3. If no — it's just a one-off mistake or context-specific judgment call, don't pollute the config. Save as a feedback memory instead if it's likely to recur.
4. Be honest about the distinction. Not every correction warrants a config change. Only codify things that are generalizable across repos and sessions.
