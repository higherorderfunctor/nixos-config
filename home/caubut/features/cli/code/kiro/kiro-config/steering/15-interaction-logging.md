# Interaction Logging

Analyze conversation sessions to detect patterns and improve over time.

## How It Works

Kiro automatically saves every conversation turn to SQLite database:
- Linux: `~/.local/share/kiro-cli/data.sqlite3`
- macOS: `~/Library/Application Support/kiro-cli/data.sqlite3`

Sessions stored per-directory with full transcripts. No manual saving needed.

## Reflection Markers

**Explicit flagging** - User types in chat (no slash):
```
reflect: Had to explain memory-first pattern again, consider promoting
```

I acknowledge: "Reflection noted: Had to explain memory-first pattern again"

**Then I immediately store in OpenMemory:**
- Tag: `interaction-analysis-reflection`
- Content: The reflection text + enough reference data to locate in SQLite transcript
- Required references: conversation ID, timestamp, surrounding context for grep/search
- Example: "Reflection during kiro-audit-2026-03-08 validation (conversation_id: abc123, ~12:13 PM, discussing reflect: marker storage)"

**Why store immediately:** Explicit `reflect:` markers indicate HIGH PRIORITY issues that are really bugging the user. These need to be recorded immediately, not discovered later through weekly analysis.

**Why include references:** During analysis, I need to pull up the full conversation context from SQLite to understand what led to the reflection.

**Why no slash:** CLI intercepts all `/commands` before I see them. Using `reflect:` (no slash) lets me detect it in message text.

## Correction Signals

**Explicit signals** (high confidence):
- `reflect: [annotation]` → explicit-reflection
- User says "no, do X instead" → correction-direct
- User provides additional context after response → correction-context
- User asks "why did you do X?" → correction-confusion

**Implicit signals** (detect patterns):
- User repeats similar request → repeated-reminder
- User corrects tool choice → correction-tool
- User clarifies requirements multiple times → correction-interpretation
- User provides examples (I need more context) → correction-examples
- User references steering files (I should have known) → correction-steering

## Analysis Index

Lightweight index in OpenMemory (tag: `interaction-analysis-index`):

```
Interaction Index (Week of YYYY-MM-DD)

Repeated Reminders (HIGH SIGNAL):
- Pattern: "Check memory before searching"
  Count: 3
  Session IDs: [session-id-1, session-id-2, session-id-3]
  
Correction Types:
- Tool choice: 3 (session IDs: [...])
- Interpretation: 2 (session IDs: [...])
- Context gaps: 1 (session IDs: [...])

Explicit Reflections (HIGHEST PRIORITY):
- Count: 2
- Memory IDs: [reflection-id-1, reflection-id-2]

Weekly Stats:
- Total sessions analyzed: 47
- Sessions with corrections: 11
- reflect: markers: 2 (stored in OpenMemory)
- Correction rate: 23% (11/47)
```

**Index is for DISCOVERY, not promotion.**
Always read full transcripts from SQLite before crafting promotion.

**Explicit reflections are already in OpenMemory** (tag: `interaction-analysis-reflection`) and should be prioritized first during analysis.

## Analysis Workflow

**Discovery (index-based):**
1. Query SQLite for sessions since last analysis
2. Parse transcripts, detect correction signals
3. Build index: pattern → count → session IDs
4. Store in OpenMemory (tag: `interaction-analysis-index`)

**Validation (full transcripts):**
1. For HIGH PRIORITY patterns (count >= 3)
2. Read full transcripts from SQLite using session IDs
3. Extract specific interactions with context
4. Verify pattern is actionable
5. Store proposals in OpenMemory (tag: `interaction-analysis-proposal`)

**Promotion:**
1. Present proposals to user (ranked by priority)
2. User reviews: Approve / Reject / Refine
3. Apply approved changes to steering files
4. Track in OpenMemory (tag: `interaction-analysis-promoted`)

## Cleanup (After Analysis)

**DELETE from OpenMemory:**
- Approved/rejected proposals
- Old index entries for promoted patterns

**UPDATE in OpenMemory:**
- Last analysis date (tag: `interaction-analysis-state`)
- Regenerated index (remove promoted patterns)

**NO CLEANUP of SQLite:**
- Kiro manages database lifecycle
- Session transcripts remain permanent

## Weekly Reminder

Check memory for "Last interaction analysis" date at session start.

If 7+ days AND 10+ flagged interactions:
- Prompt: "Your interaction log has N flagged items. Want to run analysis?"
- If yes: Invoke interaction-analysis skill
- If no: Update "Last interaction analysis" date (snooze)

Track reminder state in memory (tag: `interaction-analysis-state`).

## Repeated Reminder Detection

When user corrects me, extract the "reminder" (what they're teaching me).

**Process:**
1. Detect correction signal (explicit or implicit)
2. Extract pattern: "User wants me to do X before Y"
3. Check index: Have they said this before?
4. If yes: Increment count, update session IDs
5. If count >= 3: Flag as HIGH PRIORITY for promotion

**This is the key signal** - user training me on the same thing repeatedly.

## Confidence Building Metrics

Track to measure if learning system is working:

**Leading indicators** (early signals):
- Correction rate: Fewer corrections over time
- First-try success rate: More tasks succeed without iteration
- reflect: frequency: Fewer explicit callouts needed
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
- Uses SQLite database (Kiro's built-in session management)
- Uses OpenMemory (analysis metadata only)
- Uses agent skills (interaction-analysis)
- Uses steering lifecycle (migrations/, _archive/)

New additions:
- This steering file
- interaction-analysis skill (separate file)
- OpenMemory tagging convention
- reflect: command (message-based detection)
