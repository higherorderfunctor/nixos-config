# Interaction Analysis Skill

Analyze interaction logs to find patterns worth codifying in steering files.

## Trigger

- **Manual**: User invokes with `/skill interaction-analysis` or asks "analyze my interactions"
- **Automatic**: Weekly reminder if 10+ flagged interactions (via 15-interaction-logging.md)

## Process

### 1. Read Index

Load `interaction-index` from OpenMemory (tag: `interaction-index`, workspace: `global`).

Index provides:
- Repeated reminders with counts and log IDs
- Correction types with counts and log IDs
- Weekly stats

### 2. Identify Patterns

**HIGH PRIORITY** (repeated reminders, count >= 3):
- User teaching me the same thing multiple times
- Strong signal for steering promotion

**MEDIUM PRIORITY** (correction clusters, 2-3 similar):
- Tool choice corrections
- Interpretation misunderstandings
- Context gaps

**LOW PRIORITY** (single occurrences):
- Note for future, not ready for promotion

### 3. Validate with Full Logs

For each HIGH/MEDIUM priority pattern:
1. Read FULL LOGS from OpenMemory using log IDs
2. Understand context:
   - What was I missing?
   - What was the user teaching me?
   - Is this really a pattern or coincidence?
3. Verify it's actionable (can be expressed as a rule)

**CRITICAL**: Don't rely on index alone. Full logs provide context.

### 4. Craft Proposals

For each validated pattern, generate:

**Evidence** (cite specific interactions):
- Date, user message, my response, outcome
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

### 5. Rank by Impact

Sort proposals by:
1. Frequency (how many times repeated)
2. Severity (how much friction it caused)
3. Actionability (how clear the rule is)

### 6. Present to User

Output format:

```
Interaction Analysis (Week of YYYY-MM-DD)

═══════════════════════════════════════════════════════════
HIGH PRIORITY (repeated 3+ times)
═══════════════════════════════════════════════════════════

1. Pattern: "Check memory before searching"
   Count: 5 occurrences
   
   Evidence from full logs:
   
   • 2026-03-02: User asked about Effect patterns, I searched Kagi first
     User: "Did you check memory? We researched this last week"
     
   • 2026-03-05: User asked about Nix config, I searched web
     User: "Check memory before searching external sources"
     
   • 2026-03-08: User asked about steering lifecycle, I used Kagi
     User: "Memory first, then search. This is the 3rd time."
     
   • 2026-03-09: User asked about observer pattern, I searched web
     User: "We discussed this yesterday, check memory"
     
   • 2026-03-09: User asked about drift tool, I used Kagi
     User: "Check memory - we researched this in the audit"
   
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

Correction rate: 23% (11/47 interactions)
Baseline: Week 2 (first measurement)
Most common: Tool choice corrections (5)
Trend: N/A (first analysis)

Next analysis: 2026-03-16 (or when 10+ new flagged interactions)
```

## Cleanup After Audit

After user reviews proposals:

### 1. Categorize Logs

For each log in OpenMemory:
- **PROMOTED**: Pattern became steering rule → DELETE
- **SMOOTH**: No corrections, successful first-try → DELETE
- **FRICTION (non-promoted)**: Correction but not promoted → KEEP (might repeat)
- **RECENT**: Last 2 weeks → KEEP

### 2. Delete Logs

Use `openmemory_delete` for promoted and smooth logs.

### 3. Regenerate Index

Query remaining logs, rebuild index:
- Repeated reminders (only non-promoted)
- Correction types (only non-promoted)
- Updated weekly stats

### 4. Track Cleanup

Store in memory:
```
Last interaction cleanup: YYYY-MM-DD
Logs deleted: N promoted, M smooth
Logs kept: X friction, Y recent
```

## Validation (Feedback Loop)

After promoting a pattern, track effectiveness:

**Week N**: Promoted "check memory before searching"
**Week N+1**: Track correction rate for memory-related issues
**Week N+2**: If corrections decreased → pattern works
**Week N+2**: If corrections same/increased → pattern incomplete, refine

Store validation results in memory for future reference.

## Output to User

Present proposals in ranked order (HIGH → MEDIUM → LOW).

For each proposal:
- ✅ Approve: I add to steering file (via migrations/ or direct update)
- ❌ Reject: Not a real pattern, delete from index
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
