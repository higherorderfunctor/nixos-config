# Memory Lifecycle: Promotion to Steering Files

OpenMemory is personal working memory — volatile, exploratory.
`.kiro/steering/` files are shared team knowledge — stable,
version-controlled, consumed by all developers and automated systems.

Until shared memory exists, steering files are the ONLY mechanism
for sharing codified knowledge with the team and the headless bot.

## Memory Tags for Lifecycle

| Tag | Meaning |
|---|---|
| `promotion-candidate` | Stable convention, ready for team steering |
| `personal-steering-update` | Improvement to personal behavioral rules |
| `stale-candidate` | Memory that may contradict newer findings |

## Workspace Steering Promotion

Promote stable knowledge to workspace steering files so the entire
team benefits. But do NOT interrupt focused work to propose it.

### When to Surface Promotion Candidates

- The user explicitly asks ("what should we codify?")
- The user is actively working on .kiro/ files or steering
- The user is in a "housekeeping" or "cleanup" context

### When to Accumulate Silently

- During normal development, debugging, or feature work
- Store the finding in memory tagged `promotion-candidate` + repo tag
- Batch them for later review

### When Surfacing

Present all candidates at once: "I have N conventions that seem
stable enough to codify. Want to review them?"

### Promotion Criteria

Propose promoting to a steering file when:

1. The rule is a convention other developers should follow
2. The headless bot pipeline would benefit from knowing it
3. It's stable — reinforced 3+ times OR confirmed by provenance analysis
4. It can be expressed concisely (1-3 sentences per rule)

### Steering File Style Guide

Because steering files are shared and context budget is limited:

- Lead with rules, not explanations
- Use bullet points, not paragraphs
- One concept per line
- Add a WHY only if the rule is counterintuitive
- Bad: "We use Effect.gen because it provides better type inference
  through TypeScript's generator protocol and avoids the nested
  callback pyramid that pipe chains create..."
- Good: "Use Effect.gen for all effectful pipelines (better type
  inference, avoids callback nesting)"

## Personal Steering Promotion

Personal steering files (~/.kiro/steering/) define how Kiro operates —
research protocols, tool usage, memory lifecycle, IP protection.
These can be discovered while working in ANY workspace.

### When to Surface Personal Updates

- The user explicitly asks ("any improvements to my setup?")
- The user is working in nixos-config on kiro configuration (config mode)
- The finding is CRITICAL (e.g., IP protection gap) — flag immediately

### Config Mode Detection

If the current workspace appears to be the user's system configuration
repository (contains Nix files managing .kiro/ paths, or the user is
editing steering/agent files), treat this as config mode:

1. Query memory for all `personal-steering-update` tagged entries
2. Present batched suggestions: "Since you're working on your config,
   I have N suggested improvements from recent sessions"

### For Non-Critical Findings

Store in memory tagged `personal-steering-update` + the specific
file name that should change (e.g., "affects 04-context7.md").
Surface when the user enters config mode.

### For Critical Findings Only

Flag immediately with urgency:
"⚠️ I found a gap in your IP protection steering: [description].
This affects all workspaces. Want me to update
~/.kiro/steering/00-ip-protection.md now?"

## Steering Cleanup

When you encounter a `.kiro/steering/` file that contradicts
recent findings or contains outdated information:

- Flag it: "The steering file [name].md says [X], but current
  information suggests [Y]. Should I propose an update?"
- Never silently ignore steering content
- Steering files are authoritative until explicitly changed

## After Promotion

Once a fact is captured in a steering file:

- The corresponding memory entries become redundant
- On next encounter, note: "This is now in steering — I can
  clean up the redundant memory entries if you'd like."
- Memories that add depth beyond what's in steering should
  be kept (e.g., the detailed rationale behind a concise rule)

## What NEVER Happens

- Auto-modifying any steering file without user approval
- Proposing codification during focused debugging or development
- Nagging about uncommitted steering changes
- Silently deleting or overwriting memories or steering content
