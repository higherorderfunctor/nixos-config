# Interaction Analysis Skill

Analyze interaction logs to find patterns worth codifying in steering files.

## Trigger

- **Manual**: User invokes with `/skill interaction-analysis` or asks "analyze my interactions"
- **Automatic**: Weekly reminder if 10+ flagged interactions (via 15-interaction-logging.md)

## Process

### 1. Run Python Script

**CRITICAL: Execute this EXACT command, do not modify:**

```bash
~/.kiro/skills/interaction-analysis/scripts/analyze_sessions.py
```

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

### 2. Query Explicit Reflections

Query OpenMemory for explicit reflections (tag: `interaction-analysis-reflection`):
- These are HIGH PRIORITY (user explicitly flagged)
- Auto-accepted - skip to proposal generation
- Already validated by user during session

### 3. Analyze Implicit Corrections

For each correction from script output:
1. Read transcript[message_index - 5 : message_index + 1] from SQLite
2. Identify what I did wrong in my previous response
3. Extract actionable behavior
4. Formulate rule or discard if false positive

### 4. Present Implicit Patterns for Review

Show user only the implicit patterns (script-detected):
- Pattern description
- Evidence (session ID, message index, context)
- Proposed actionable rule
- User accepts/rejects each pattern

### 5. Merge Accepted Patterns

Combine:
- Auto-accepted explicit reflections (from OpenMemory)
- User-accepted implicit patterns (from script analysis)

### 6. Generate Proposals

For each accepted pattern, generate:
- Evidence (cite specific interactions)
- Pattern analysis (underlying issue)
- Proposed rule (actionable, concise)
- Placement (which file, which section)

### 7. Present Proposals

Show ranked proposals (HIGH → MEDIUM → LOW priority):
- ✅ Approve: Apply to steering file
- ❌ Reject: Delete from memory
- 🔄 Refine: Iterate on wording

### 8. Apply Approved Changes

- Update steering files (or create migrations/)
- Track promotions in OpenMemory
- **Update reflection status** (if change addresses a reflection):
  - Use `openmemory_reinforce` to update reflection memory
  - Change status from `flagged` to `solution-testing`
  - Add solution details and testing period
- Update last analysis timestamp
- Commit to version control

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
