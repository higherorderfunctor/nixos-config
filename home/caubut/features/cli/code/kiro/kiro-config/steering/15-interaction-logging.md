# Interaction Logging

Log corrections and learning patterns to improve over time.

## What to Log

Store in OpenMemory with tags: `interaction-log`, workspace, date, unique log-id

**Full interaction context:**
- User message
- My response
- Tools used
- Outcome (success / correction / clarification)
- Active steering files (what I should have known)
- Workspace identifier

**Explicit signals** (high confidence):
- `/reflect: [annotation]` command → tag: `explicit-reflection`
- User says "no, do X instead" → tag: `correction-direct`
- User provides additional context after response → tag: `correction-context`
- User asks "why did you do X?" → tag: `correction-confusion`

**Implicit signals** (detect patterns):
- User repeats similar request → tag: `repeated-reminder`
- User corrects tool choice → tag: `correction-tool`
- User clarifies requirements multiple times → tag: `correction-interpretation`
- User provides examples (I need more context) → tag: `correction-examples`
- User references steering files (I should have known) → tag: `correction-steering`

## Summary/Index

Maintain lightweight index in memory (tag: `interaction-index`, workspace: `global`):

```
Interaction Index (Week of YYYY-MM-DD)

Repeated Reminders (HIGH SIGNAL):
- Pattern: "Check memory before searching"
  Count: 3
  Log IDs: [id1, id2, id3]
  
Correction Types:
- Tool choice: 3 (log IDs: [id4, id5, id6])
- Interpretation: 2 (log IDs: [id7, id8])
- Context gaps: 1 (log IDs: [id9])

Weekly Stats:
- Total interactions: 47
- Flagged interactions: 11
- /reflect count: 2
- Correction rate: 23% (11/47)
```

**Index is for DISCOVERY, not promotion.**
Always read FULL LOGS before crafting promotion.

Update index incrementally after each correction (not batch).

## Analysis Workflow

**Discovery (index-based):**
1. Index identifies pattern: "repeated reminder, count: 3"
2. Index provides log IDs: [id1, id2, id3]

**Validation (full logs):**
3. Read FULL LOGS for those IDs from OpenMemory
4. Understand context:
   - What was I missing?
   - What was the user teaching me?
   - Is this really a pattern or coincidence?
5. Craft promotion with evidence (not assumptions)

**Promotion:**
6. Present proposal with evidence from full logs
7. User reviews: Approve / Reject / Refine
8. If approved: Add to steering file (via migrations/ or direct update)
9. Track: "Promoted pattern X on YYYY-MM-DD from logs [id1, id2, id3]"

## Cleanup (After Audit)

Keep memory bounded with rolling window.

**DELETE:**
- Promoted logs (pattern now in steering, no longer needed)
- Smooth transactions (no corrections, no learning signal)
- Stale logs (>2 weeks, unless friction)

**KEEP:**
- Friction points (not promoted, might repeat)
- Recent logs (last 2 weeks)

**After cleanup:**
- Regenerate index from remaining logs
- Update weekly stats
- Track cleanup date in memory

## Retention Policy

- **Active logs**: Last 2 weeks
- **Friction points**: Until promoted or 4 weeks (whichever first)
- **Promoted patterns**: Track in steering file metadata, delete logs
- **Index**: Regenerate after cleanup, always current

## /reflect Command

User types `/reflect: [annotation]` in chat to explicitly flag interaction.

**Example:**
```
/reflect: Had to explain memory-first pattern again, consider promoting
```

I detect this and store with:
- Full context (user message + my response + tools used)
- User annotation
- Tags: `interaction-log`, `explicit-reflection`, workspace, date
- Outcome: explicit-callout

## Weekly Reminder

Check memory for "Last interaction analysis" date at session start.

If 7+ days AND 10+ flagged interactions:
- Prompt: "Your interaction log has N flagged items. Want to run analysis?"
- If yes: Invoke interaction-analysis skill
- If no: Update "Last interaction analysis" date (snooze)

Track reminder state in memory (tag: `interaction-reminder`, workspace: `global`).

## Repeated Reminder Detection

When user corrects me, extract the "reminder" (what they're teaching me).

**Process:**
1. Detect correction signal (explicit or implicit)
2. Extract pattern: "User wants me to do X before Y"
3. Check index: Have they said this before?
4. If yes: Increment count, update log IDs
5. If count >= 3: Flag as HIGH PRIORITY for promotion

**This is the key signal** - user training me on the same thing repeatedly.

## Confidence Building Metrics

Track to measure if learning system is working:

**Leading indicators** (early signals):
- Correction rate: Fewer corrections over time
- First-try success rate: More tasks succeed without iteration
- /reflect frequency: Fewer explicit callouts needed
- Repeated reminder count: Decreasing over time

**Baseline** (establish now, week 2):
- Current correction rate
- Current first-try success rate
- Track weekly to see improvement

**Feedback loop:**
After promoting a pattern, track if it reduces corrections.
If not, the pattern was wrong or incomplete - refine or remove.

## What NOT to Log

- Trivial Q&A (simple syntax questions)
- Successful first-try tasks (no corrections)
- Sensitive information (credentials, API keys, personal data)
- Information already in steering files (redundant)

## Integration with Existing Workflow

This builds on existing infrastructure:
- Uses OpenMemory (already have)
- Uses agent skills (already have pattern)
- Uses steering lifecycle (migrations/, _archive/)
- Uses memory for tracking (already have)

New additions:
- This steering file
- interaction-analysis skill (separate file)
- Tagging convention for OpenMemory
- /reflect command (message-based detection)
