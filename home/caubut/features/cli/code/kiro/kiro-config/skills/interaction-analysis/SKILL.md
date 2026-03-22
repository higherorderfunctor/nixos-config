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

### 0. Check for Refinement Candidates (Before Script Run)

**Query rejections:**
```
openmemory_query: "rejection patterns"
tags: ["global", "interaction-analysis-rejected"]
user_id: "caubut"
```

**Group and filter:**
- Group rejections by pattern type (extract from content)
- Filter: only patterns with 3+ rejections
- Count occurrences per pattern type

**Implementation:**
```
1. Query all rejections from memory
2. Parse each rejection to extract "Pattern Type" field
3. Group by pattern type, count occurrences
4. Filter groups where count >= 3
5. For each qualifying group:
   - Extract pattern descriptions
   - Extract rejection reasons
   - Prepare summary for user
```

**If any patterns have 3+ rejections:**
- Prompt: "Found [N] rejection patterns (3+ occurrences each). Want to refine detection before analysis?"
- Show grouped patterns with counts and rejection reasons
- Example output:
  ```
  Pattern Type: false-positive-clarification (5 occurrences)
  - "User providing context, not correcting error"
  - "User answering my question, not fixing mistake"
  - "User clarifying requirements, not pointing out bug"
  ```
- If yes → proceed to refinement (see Phase 1 Step 8)
- If no → continue to Step 1

**If no patterns meet threshold:**
- Continue silently to Step 1

### False Positive Pattern Types

When rejecting a pattern, classify it using this taxonomy:

**Common False Positive Types:**
- `false-positive-clarification` - User providing additional context or clarifying requirements (not correcting an error)
- `false-positive-question` - User asking a follow-up question (not pointing out a mistake)
- `false-positive-already-done` - User stating they already completed something (not correcting your action)
- `false-positive-acknowledgment` - User confirming understanding or saying "yes/no/ok" (not fixing anything)
- `false-positive-preference` - User expressing a preference or opinion (not correcting wrong behavior)
- `false-positive-context` - User providing background information (not identifying an error)
- `false-positive-exploration` - User exploring options or brainstorming (not steering away from mistake)

**How to classify:**
1. Read the rejection reason
2. Identify why it's not a real correction
3. Match to closest pattern type above
4. If unclear, use `false-positive-other` and note the reason

**Example:**
- Rejection reason: "User was just answering my question about their preference"
- Pattern Type: `false-positive-preference`


### 1. Check Last Analysis Timestamp

Query OpenMemory for last analysis state (tag: `interaction-analysis-state`):
```
openmemory_query: "last analysis timestamp"
tags: ["global", "interaction-analysis-state"]
```

If found, extract timestamp and display trend summary:
- "Last analysis: [date], [N] corrections, [X]% false positive rate"
- "Trend: Corrections [up/down/stable], FP rate [up/down/stable]"

If not found, analyze all sessions.

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
        {
          "message_index": 10,
          "user_message": "...",
          "context_messages": 7,
          "summary": "ERROR: ...\nCAUSE: ...\nCORRECTION: ...\nPATTERN: ...\nCONTEXT: ..."
        }
      ]
    }
  ]
}
```

### 3. Store Corrections to Memory (Automatic - No Prompt)

**CRITICAL: Script output is in tool response stdout, NOT temp files**

**Storage Strategy:**

**For small datasets (<100 corrections):**
Store each correction individually:
```
openmemory_store:
  content: |
    Correction from session [session_id]
    Workspace: [workspace]
    Message Index: [message_index]
    
    User Message: [user_message]
    
    Summary:
    [full summary with ERROR/CAUSE/CORRECTION/PATTERN/CONTEXT markers]
  tags: ["global", "interaction-analysis-unreviewed", "workspace-tag"]
  type: "contextual"
  user_id: "caubut"
```

**For large datasets (100+ corrections):**
Store in compressed batches (50-100 per entry):
```
openmemory_store:
  content: |
    Interaction Analysis - Corrections Batch N (Corrections X-Y)
    
    Session: [session_id]
    Workspace: [workspace]
    
    Corrections:
    1. [msg N] User: "..." - ERROR: ... PATTERN: ...
    2. [msg N] User: "..." - ERROR: ... PATTERN: ...
    [... 50-100 corrections per batch]
  tags: ["global", "interaction-analysis-unreviewed", "workspace-tag", "batch-N"]
  type: "contextual"
  user_id: "caubut"
```

**Implementation:**
- Parse JSON from tool response (already in context)
- Choose strategy based on correction count
- Show progress: "Storing corrections: X/Y"
- Store metadata summary at end (total counts, timestamp)

**DO NOT:**
- ❌ Look for temp files (output is in tool response)
- ❌ Redirect to filesystem
- ❌ Use subagents (they don't have access to tool response)

### 4. Extract Patterns and Filter (Automatic - Reduce 500+ to 20-30)

**GOAL:** Transform raw corrections into actionable patterns. User reviews PATTERNS, not individual corrections.

**Process:**

1. **Load all corrections** from memory (tag: `interaction-analysis-unreviewed`)

2. **Extract patterns** - Parse PATTERN field from each correction summary

3. **Group by similarity** - Cluster corrections with similar patterns together

4. **Check existing coverage:**
   ```
   openmemory_query: "explicit reflections and accepted patterns"
   tags: ["global", "interaction-analysis-reflection"]
   user_id: "caubut"
   ```
   ```
   openmemory_query: "accepted patterns"
   tags: ["global", "interaction-analysis-accepted"]
   user_id: "caubut"
   ```
   - If pattern already exists, merge evidence (don't duplicate)
   - Reinforce existing memory with new evidence count

5. **Classify pattern type:**
   - `missing-instruction` - Gap in steering files
   - `context-dilution` - Architectural issue needing rearchitecture
   - `false-positive` - Not actually a correction

6. **Rank by ROI:**
   - **HIGH**: 3+ instances + (missing-instruction OR context-dilution) + not in steering
   - **MEDIUM**: 2 instances + actionable + not covered
   - **LOW**: Single instance OR already covered OR false positive

7. **Store HIGH/MEDIUM patterns only:**
   ```
   openmemory_store:
     content: |
       Pattern: [description]
       Type: missing-instruction | context-dilution
       Evidence: [count] occurrences
       Sessions: [id1, id2, id3, ...]
       Message indices: [10, 25, 8, ...]
       Priority: HIGH | MEDIUM
       Status: pending-review
     tags: ["global", "interaction-analysis-pattern", "nixos-config", "priority-high"]
     type: "contextual"
   ```

8. **Delete LOW ROI items** - Remove from memory, track count for metrics

9. **Track rejection reasons** - For Ollama tuning feedback loop

**Lean storage approach:**
- Store pattern summary + evidence count
- Store session IDs + message indices for lookup
- Don't pack every detail - user can drill in when reviewing
- Keep memory lean with references, not full facts

**Show progress:**
- "Extracting patterns: Found X unique patterns from Y corrections"
- "Filtered to Z high-ROI patterns (HIGH: A, MEDIUM: B)"
- "Removed W low-ROI items"

**Expected outcome:** 500+ corrections → 20-30 actionable patterns

### 5. Query Explicit Reflections

Query OpenMemory for explicit reflections (tag: `interaction-analysis-reflection`):
- Filter by status: `flagged` or `solution-testing`
- These are HIGH PRIORITY (user explicitly flagged)
- If new patterns match existing reflections → reinforce reflection, don't duplicate

### 6. Update Analysis State

Store completion timestamp and metrics in OpenMemory (tag: `interaction-analysis-state`):
```
Last analysis completed: YYYY-MM-DD HH:MM
Sessions analyzed: [count]
Corrections detected: [count]
Corrections stored (after filtering): [count]
False positives removed: [count]
Pending items: [count]
Status: ready-for-review

Metrics:
- Total corrections detected: [count]
- False positives this run: [count]
- Corrections accepted: [count from previous analyses]
- Corrections rejected: [count from previous analyses]
- Acceptance rate: [accepted / (accepted + rejected) * 100]%
- False positive rate: [(FP this run + rejected) / total * 100]%
- Refinements applied: [count]
- Last refinement date: [date or null]
- Refined pattern types: [list or empty]

Trend (compare to previous analysis):
- Correction count: [increased/decreased/stable]
- False positive rate: [increased/decreased/stable]
```

**Phase 1 complete.** Wait for user to initiate Phase 2.

### 7. Refinement Process (Optional - Triggered from Step 0)

**When user confirms refinement in Step 0:**

1. **Review rejection clusters:**
   - Show each pattern type with 3+ rejections
   - Display rejection reasons for each cluster
   - Ask: "Add this as negative example to Ollama prompt?"

2. **Generate updated prompt:**
   - For each approved cluster, create negative example
   - Format: "NOT a correction: [pattern description]"
   - Example: "NOT a correction: user saying 'already did that' without error"
   - Show complete updated prompt to user

**Implementation:**
```
1. For each approved pattern type:
   - Extract common characteristics from rejection reasons
   - Generate negative example description
   - Format: "NOT a correction: [description]"

2. Read current prompt from analyze_sessions.py
3. Add negative examples to classification instructions
4. Show full updated prompt with changes highlighted
```

3. **User approval:**
   - Display full prompt with negative examples highlighted
   - Ask: "Approve this prompt update?"
   - If rejected: iterate or skip refinement

4. **Update script:**
   - If approved: update analyze_sessions.py with new prompt
   - Use code tool to modify CLASSIFICATION_PROMPT variable
   - Test on recent sessions to verify improvement
   - Mark refined patterns (tag: `interaction-analysis-refined`)

**Implementation:**
```
1. Store current prompt version (before updating):
   openmemory_store:
     content: |
       Prompt Version - [date]
       
       Refinement ID: [unique ID]
       Refined patterns: [list of pattern IDs]
       
       Prompt text:
       [full CLASSIFICATION_PROMPT content]
     tags: ["global", "interaction-analysis-prompt-history", "nixos-config"]
     type: "contextual"

2. Use code tool to update analyze_sessions.py:
   - Locate CLASSIFICATION_PROMPT variable
   - Add negative examples to prompt text
   - Preserve existing structure

3. Test updated prompt:
   - Run script on last 10 sessions (or all from last 7 days if fewer)
   - Compare: corrections detected with old vs new prompt
   - Review each detection: any false positives for refined patterns?
   - Success criteria:
     * Zero false positives for refined pattern types
     * No new false positive types introduced
     * Similar or lower total correction count (not higher)
   - If criteria not met: iterate on negative examples or revert
   - Show comparison: "Old: 25 corrections (5 FP), New: 22 corrections (0 FP for refined types)"

4. Store refinement record:
   openmemory_store:
     content: |
       Prompt Refinement - [date]
       
       Added negative examples:
       - [pattern type 1]: [description]
       - [pattern type 2]: [description]
       
       Refined patterns: [list of pattern IDs]
     tags: ["global", "interaction-analysis-refined", "nixos-config"]
     type: "contextual"
```

5. **Continue to Step 1:**
   - Proceed with normal Phase 1 workflow
   - Script will use updated prompt for this analysis

### 8. Ollama Tuning Feedback Loop (Automatic)

**Triggered during Step 4 pattern extraction:**

When LOW ROI patterns are identified (single instance, false positives, already covered):

1. **Track rejection reasons** - Store why pattern was rejected
2. **Group by pattern type** - Cluster similar rejections
3. **Store for future refinement:**
   ```
   openmemory_store:
     content: |
       Auto-Rejected Pattern: [description]
       
       Rejection Reason: [why it's low ROI]
       Pattern Type: [classification]
       
       Evidence:
       - Session: [session_id]
       - Message Index: [message_index]
     tags: ["global", "interaction-analysis-rejected", "nixos-config"]
     type: "contextual"
   ```

4. **Next run Step 0** - These rejections feed refinement candidates

**This creates a feedback loop:**
- Ollama detects too many false positives
- Step 4 filters them out
- Rejections accumulate in memory
- Step 0 (next run) offers to refine Ollama prompt
- Fewer false positives in future runs

---

## Phase 2: Review & Fix (User-Driven)

### Commands

**"show pending"** - Display patterns awaiting accept/reject
- Load from OpenMemory (tag: `interaction-analysis-pattern`)
- Group by priority (HIGH → MEDIUM)
- Show pattern summary with evidence count
- User can drill into specific sessions/messages for details

**"show accepted"** - Display accepted patterns with status
- Load from OpenMemory (tag: `interaction-analysis-accepted`)
- Show status: flagged / solution-testing / verified
- Include solution details if in testing

**"accept X"** - Accept a pending pattern
- Move from `pending` to `accepted` tag
- Set status: `flagged`
- Track acceptance for metrics
- Ready for "work on X"

**Implementation:**
```
1. Load pending pattern by ID or index
2. Move to accepted:
   openmemory_store:
     content: [original pattern content]
     tags: ["global", "interaction-analysis-accepted", "nixos-config"]
     status: "flagged"
3. Delete original pending pattern
4. Update metrics: increment acceptance count
5. Confirm: "Pattern accepted and ready for implementation"
```


**"reject X"** - Reject a pending pattern
- Prompt user for rejection reason
- Store rejection in OpenMemory (tag: `interaction-analysis-rejected`)
- Format: pattern description + rejection reason + evidence (session_id + message_index)
- Used for refinement: patterns with 3+ rejections trigger prompt update
- Delete original pending pattern from memory

**Implementation:**
```
1. Load pending pattern by ID or index
2. Prompt: "Why are you rejecting this pattern? (helps improve detection)"
3. User provides reason
4. Classify false positive type:
   - Review rejection reason
   - Match to taxonomy (see "False Positive Pattern Types" section)
   - If unclear, prompt: "Which false positive type? (clarification/question/already-done/...)"
5. Store rejection:
   openmemory_store:
     content: |
       Rejected Pattern: [pattern description]
       
       Rejection Reason: [user's reason]
       
       Evidence:
       - Session: [session_id]
       - Message Index: [message_index]
       - Context: [brief context from original pattern]
       
       Pattern Type: [classification from taxonomy]
     tags: ["global", "interaction-analysis-rejected", "nixos-config"]
     type: "contextual"
6. Delete original pending pattern (openmemory_delete)
7. Confirm: "Pattern rejected as [type] and stored for refinement analysis"
```

**"rollback refinement X"** - Revert a prompt refinement
- Query prompt history for refinement ID X
- Restore previous prompt to analyze_sessions.py
- Mark refinement as reverted
- Test on recent sessions to verify restoration

**When to use:**
- Refinement increased false positive rate
- Refinement introduced new false positive types
- Refinement reduced true positive detection

**"work on X"** - Generate proposal and apply changes

**Query both datasets:**
```
# Accepted patterns from analysis
openmemory_query: "accepted patterns"
tags: ["global", "interaction-analysis-accepted"]
user_id: "caubut"

# Flagged reflections
openmemory_query: "flagged reflections"
tags: ["global", "interaction-analysis-reflection"]
user_id: "caubut"
filter: status = "flagged"
```

**For each item:**
1. Read full context (pattern description, evidence, root cause)
2. Identify target steering file(s)
3. Generate specific proposal (what to add/change/remove)
4. Present to user for approval
5. If approved: apply changes, update status to "solution-proposed"
6. Track promotion in memory

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
