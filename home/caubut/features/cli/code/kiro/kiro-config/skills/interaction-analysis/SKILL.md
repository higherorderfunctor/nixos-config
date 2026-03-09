# Interaction Analysis Skill

Analyze interaction logs to find patterns worth codifying in steering files.

## Trigger

- **Manual**: User invokes with `/skill interaction-analysis` or asks "analyze my interactions"
- **Automatic**: Weekly reminder if 10+ flagged interactions (via 15-interaction-logging.md)

## Process

### 1. Query SQLite Database

Read sessions from Kiro's database:
- Linux: `~/.local/share/kiro-cli/data.sqlite3`
- macOS: `~/Library/Application Support/kiro-cli/data.sqlite3`

Query `conversations_v2` table for sessions since last analysis:
```sql
SELECT key, conversation_id, value, created_at, updated_at
FROM conversations_v2
WHERE updated_at > <last_analysis_timestamp>
ORDER BY updated_at DESC
```

Get last analysis timestamp from OpenMemory (tag: `interaction-analysis-state`).

### 2. Parse Transcripts

For each session, parse the transcript (array of strings):
- User messages start with "> " (prompt indicator)
- Assistant messages have no prefix
- Extract user messages and my responses

### 3. Detect Correction Signals

**Explicit signals:**
- `reflect:` in user message → explicit-reflection
- "no, " or "actually, " or "instead, " → correction-direct
- "why did you" or "what made you" → correction-confusion

**Implicit signals:**
- User provides additional context after my response → correction-context
- User repeats similar request → repeated-reminder
- User mentions tool choice → correction-tool
- Multiple clarifications → correction-interpretation

### 4. Build Index

Store in OpenMemory (tag: `interaction-analysis-index`):

```
Interaction Index (Week of YYYY-MM-DD)

Repeated Reminders (HIGH SIGNAL):
- Pattern: "Check memory before searching"
  Count: 3
  Session IDs: [session-id-1, session-id-2, session-id-3]
  
Correction Types:
- Tool choice: 3 (session IDs: [...])
- Interpretation: 2 (session IDs: [...])

Weekly Stats:
- Total sessions: 47
- Sessions with corrections: 11
- Correction rate: 23%
```

### 5. Validate with Full Transcripts

For HIGH PRIORITY patterns (count >= 3):

1. Read full transcripts from SQLite using session IDs
2. Extract specific interactions:
   - User message
   - My response
   - What went wrong
3. Understand context:
   - What was I missing?
   - What was the user teaching me?
   - Is this really a pattern or coincidence?
4. Verify it's actionable (can be expressed as a rule)

**CRITICAL**: Don't rely on index alone. Full transcripts provide context.

### 6. Craft Proposals

For each validated pattern, generate:

**Evidence** (cite specific interactions):
- Date, session ID, user message, my response, outcome
- What went wrong? What should I have done?

**Pattern** (what's the underlying issue):
- "I'm not checking memory before external searches"
- "I'm using Kagi when Context7 would be better"
- "I'm not reading steering files at session start"

**Proposed Rule** (actionable, concise):
- "Before any web search, query OpenMemory for prior findings"
- "For library questions, check Context7 before Kagi"
- "At session start, read .kiro/steering/ structure"

**Placement** (which steering file, which section):
- Personal vs workspace
- Which file (01-tool-usage.md, 02-research-depth.md, etc.)
- Which section within file

Store proposals in OpenMemory (tag: `interaction-analysis-proposal`).

### 7. Rank by Impact

Sort proposals by:
1. Frequency (how many times repeated)
2. Severity (how much friction it caused)
3. Actionability (how clear the rule is)

### 8. Present to User

Output format:

```
Interaction Analysis (Week of YYYY-MM-DD)

═══════════════════════════════════════════════════════════
HIGH PRIORITY (repeated 3+ times)
═══════════════════════════════════════════════════════════

1. Pattern: "Check memory before searching"
   Count: 5 occurrences
   
   Evidence from full transcripts:
   
   • 2026-03-02 (session abc123): User asked about Effect patterns, I searched Kagi first
     User: "Did you check memory? We researched this last week"
     
   • 2026-03-05 (session def456): User asked about Nix config, I searched web
     User: "Check memory before searching external sources"
     
   • 2026-03-08 (session ghi789): User asked about steering lifecycle, I used Kagi
     User: "Memory first, then search. This is the 3rd time."
   
   Pattern Analysis:
   I'm not checking OpenMemory before external searches, causing
   redundant research and missing prior findings.
   
   Proposed Rule:
   "Before any web search or GitHub lookup, query OpenMemory for
   prior findings. This avoids redundant searches and leverages
   existing knowledge."
   
   Placement: 01-tool-usage.md, section "Memory (Always Active)"
   
   Draft Addition:
   ```markdown
   **Before external searches:**
   - Query OpenMemory first (check for prior findings)
   - If found: Use existing knowledge, reinforce memory
   - If not found: Proceed with external search, store results
   ```

───────────────────────────────────────────────────────────
MEDIUM PRIORITY (2-3 occurrences)
───────────────────────────────────────────────────────────

2. Pattern: "Use Context7 before Kagi for library questions"
   Count: 2 occurrences
   
   Evidence: [similar format]...

───────────────────────────────────────────────────────────
METRICS
───────────────────────────────────────────────────────────

Correction rate: 23% (11/47 sessions)
Baseline: Week 2 (first measurement)
Most common: Tool choice corrections (5)
Trend: N/A (first analysis)

Next analysis: 2026-03-16 (or when 10+ new flagged interactions)
```

## Cleanup After Analysis

After user reviews proposals:

### 1. Delete from OpenMemory

- Approved proposals (tag: `interaction-analysis-proposal`)
- Rejected proposals (tag: `interaction-analysis-proposal`)

### 2. Update in OpenMemory

- Last analysis date (tag: `interaction-analysis-state`)
- Regenerate index (remove promoted patterns)

### 3. Track Promotions

Store in OpenMemory (tag: `interaction-analysis-promoted`):
```
Promoted pattern: check-memory-before-search
Date: YYYY-MM-DD
File: 01-tool-usage.md
Session IDs: [...]
```

### 4. NO SQLite Cleanup

Kiro manages database lifecycle. Session transcripts remain permanent.

## Validation (Feedback Loop)

After promoting a pattern, track effectiveness:

**Week N**: Promoted "check memory before searching"
**Week N+1**: Track correction rate for memory-related issues
**Week N+2**: If corrections decreased → pattern works
**Week N+2**: If corrections same/increased → pattern incomplete, refine

Store validation results in OpenMemory (tag: `interaction-analysis-validation`).

## Output to User

Present proposals in ranked order (HIGH → MEDIUM → LOW).

For each proposal:
- ✅ Approve: I add to steering file (via migrations/ or direct update)
- ❌ Reject: Not a real pattern, delete from OpenMemory
- 🔄 Refine: Good idea, but needs better wording (iterate)

After user decisions:
- Apply approved changes
- Run cleanup
- Update index
- Track promotion effectiveness

## Integration with Steering Lifecycle

**For personal steering updates:**
- Minor refinements → update in place
- Pattern changes → create migration guide in migrations/
- Deprecated patterns → move to _archive/

**For workspace steering updates:**
- Follow workspace steering lifecycle (if exists)
- Otherwise, direct update with commit message

## Confidence Building

Track metrics over time:
- Week 2: Baseline (23% correction rate)
- Week 4: First promotions, track improvement
- Week 6: Review metrics, celebrate wins
- Week 8: Assess overall improvement

**Celebrate wins**: When a promoted pattern prevents a correction, note it.
This builds trust in the learning system.

## Always Evolving

This skill will evolve based on:
- False positives (refine detection rules)
- Threshold adjustments (maybe 2 is enough, not 3?)
- New correction types (discover as we go)
- User feedback (what works, what doesn't)

Continuous improvement, not big-bang deployment.
