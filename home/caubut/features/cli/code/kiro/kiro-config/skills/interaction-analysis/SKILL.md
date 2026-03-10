# Interaction Analysis Skill

Analyze interaction logs to find patterns worth codifying in steering files.

## Trigger

- **Manual**: User invokes with `/skill interaction-analysis` or asks "analyze my interactions"
- **Automatic**: Weekly reminder if 10+ flagged interactions (via 15-interaction-logging.md)

## Two-Phase Workflow

**Phase 1: Analyze**
1. User: "analyze my interactions"
2. Run script → store raw results in memory
3. Ask: "Ready to process these corrections?"
4. User confirms
5. Post-process (read context, extract patterns, reinforce reflections)
6. Store processed suggestions in memory
7. Done - wait for Phase 2

**Phase 2: Review & Fix**
- "show pending" → patterns awaiting accept/reject
- "show accepted" → accepted patterns with status (flagged/solution-testing/verified)
- "accept X" / "reject X" → update pattern status
- "work on X" → generate proposals, apply changes to steering files

## Phase 1: Analyze

### 1. Check Last Analysis Timestamp

Query OpenMemory for last analysis state (tag: `interaction-analysis-state`):
```
openmemory_query: "last analysis timestamp"
tags: ["global", "interaction-analysis-state"]
```

If found, extract timestamp. If not found, analyze all sessions.

### 2. Run Python Script

**CRITICAL: Execute this EXACT command, do not modify:**

```bash
~/.kiro/skills/interaction-analysis/scripts/analyze_sessions.py --since "YYYY-MM-DDTHH:MM:SS"
```

Replace `YYYY-MM-DDTHH:MM:SS` with the timestamp from step 1. If no prior timestamp exists (first run), omit the `--since` parameter to analyze last 7 days.

**What this does:**
- Queries SQLite for sessions since last analysis
- Uses Ollama (llama3.2:3b) to classify each user message
- Skips explicit `reflect:` markers (handled separately)
- Outputs JSON results to stdout (for parsing)
- Outputs progress to stderr (user sees real-time updates)
- Returns all results (no truncation)

**DO NOT:**
- ❌ Add `2>&1` (merges stderr into stdout, breaks JSON parsing)
- ❌ Add `head` or `tail` (truncates results - see reflection 3b423be5)
- ❌ Add `tee` (unnecessary complexity)
- ❌ Redirect output (breaks progress display)
- ❌ Modify the command in any way

**Why this matters:**
- Script designed for clean stdout/stderr separation
- Progress bar uses `\r` on stderr for live updates
- JSON output must be complete for analysis
- Truncation loses correction data
- This command has been corrected 3+ times - follow it exactly

**Output format:**
```json
{
  "analyzed_at": "2026-03-09T...",
  "total_sessions": 41,
  "sessions_with_patterns": 18,
  "results": [
    {
      "session_id": "abc123...",
      "workspace": "project-name",
      "corrections": [
        {"message_index": 10, "user_message": "..."}
      ]
    }
  ]
}
```

### 3. Store Raw Script Output

**CRITICAL: Capture output from tool response, NOT from filesystem**

The script outputs JSON to stdout. The execute_bash tool returns this in the response. Store that directly:

```
1. Run script (output comes back in tool response)
2. Parse JSON from stdout field
3. Store in OpenMemory with tag: interaction-analysis-raw
```

**DO NOT:**
- ❌ Redirect to temp file (`> /tmp/file.json`)
- ❌ Write to filesystem first
- ❌ Use intermediate files

**Why:** Tool response already contains the output. No filesystem needed.

**State tracking:**
- Update state: `script-complete, awaiting-post-process`
- Enables resumability if interrupted

### 4. Post-Process with Conversation History

**CRITICAL: Process ALL corrections from script output, not just samples**

For each correction in the script results, read SQLite context and analyze:

```bash
sqlite3 ~/.local/share/kiro-cli/data.sqlite3 \
  "SELECT value FROM conversations_v2 WHERE conversation_id = '<session_id>' LIMIT 1" | \
  python3 -c "
import json, sys
data = json.load(sys.stdin)
transcript = data.get('transcript', [])
# Get context: 5 messages before + correction message
start = max(0, <message_index> - 5)
end = <message_index> + 1
context = transcript[start:end]
for i, msg in enumerate(context, start=start):
    print(f'[{i}] {msg[:200]}')
"
```

**Then analyze each correction:**
1. Read the context to understand what went wrong
2. Identify the root cause (not just the symptom)
3. Extract actionable pattern or discard if false positive
4. Store as individual pending item (see step 6)

**Example:** User says "use conventional commits" → Pattern: "Default to conventional commits unless workspace has different convention"

**DO NOT skip corrections** - process all of them to ensure complete analysis.

### 5. Query Explicit Reflections

Query OpenMemory for explicit reflections (tag: `interaction-analysis-reflection`):
- Filter by status: `flagged` or `solution-testing`
- These are HIGH PRIORITY (user explicitly flagged)
- If new patterns match existing reflections → reinforce reflection, don't duplicate

### 6. Store Individual Pending Items

For each actionable pattern, store in OpenMemory (tag: `interaction-analysis-pending`):
```
Pattern: [description]
Evidence: session_id + message_index + context
Priority: HIGH/MEDIUM/LOW
Related reflection: [reflection_id or null]
Status: pending-review
```

### 7. Update Analysis State

Store completion timestamp in OpenMemory (tag: `interaction-analysis-state`):
```
Last analysis completed: YYYY-MM-DD HH:MM
Sessions analyzed: [count]
Corrections processed: [count]
Pending items: [count]
Status: ready-for-review
```

**Phase 1 complete.** Wait for user to initiate Phase 2.

---

## Phase 2: Review & Fix (User-Driven)

### Commands

**"show pending"** - Display patterns awaiting accept/reject
- Load from OpenMemory (tag: `interaction-analysis-pending`)
- Group by priority (HIGH → MEDIUM → LOW)
- Show evidence and proposed rule

**"show accepted"** - Display accepted patterns with status
- Load from OpenMemory (tag: `interaction-analysis-accepted`)
- Show status: flagged / solution-testing / verified
- Include solution details if in testing

**"accept X"** - Accept a pending pattern
- Move from `pending` to `accepted` tag
- Set status: `flagged`
- Ready for "work on X"

**"reject X"** - Reject a pending pattern
- Delete from memory
- Note rejection reason (helps refine detection)

**"work on X"** - Generate proposal and apply changes

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
