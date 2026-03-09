# Interaction Analysis Skill

Analyzes your conversation sessions with Kiro to detect patterns and suggest steering file improvements.

## What It Does

This skill helps you train Kiro to think more like you by:
1. Detecting when you repeatedly correct or clarify the same things
2. Analyzing patterns in your interactions
3. Proposing steering file updates to prevent future corrections
4. Tracking improvement over time

## How to Use

### Automatic Trigger (Weekly Reminder)

Kiro will automatically remind you weekly if you have 10+ flagged interactions:

```
Your interaction log has 15 flagged items. Want to run analysis?
```

Just say "yes" and the analysis will run.

### Manual Trigger

You can run analysis anytime by asking:

```
Analyze my interactions
```

or

```
Run interaction analysis
```

Kiro will detect this and invoke the skill.

### What You'll See

The skill presents findings in ranked order:

```
═══════════════════════════════════════════════════════════
HIGH PRIORITY (repeated 3+ times)
═══════════════════════════════════════════════════════════

1. Pattern: "Check memory before searching"
   Count: 5 occurrences
   
   Evidence from full transcripts:
   • 2026-03-02 (session abc123): [specific interaction]
   • 2026-03-05 (session def456): [specific interaction]
   ...
   
   Proposed Rule:
   "Before any web search, query OpenMemory for prior findings"
   
   Placement: 01-tool-usage.md, section "Memory (Always Active)"
```

### Review Proposals

For each proposal, you can:
- ✅ **Approve**: Kiro adds it to the steering file
- ❌ **Reject**: Not a real pattern, ignore it
- 🔄 **Refine**: Good idea, but needs better wording

Just tell Kiro your decision for each one.

### After Analysis

Kiro will:
1. Apply approved changes to steering files
2. Clean up analysis metadata from OpenMemory
3. Update the interaction index
4. Track effectiveness (did the new rule reduce corrections?)

## Logging Interactions

The skill analyzes sessions from Kiro's SQLite database.

### Automatic Logging

Kiro automatically saves every conversation turn to:
- Linux: `~/.local/share/kiro-cli/data.sqlite3`
- macOS: `~/Library/Application Support/kiro-cli/data.sqlite3`

No manual saving needed.

### Manual Flagging with reflect:

Flag important interactions explicitly:

```
reflect: Had to explain memory-first pattern again, consider promoting
```

Kiro will acknowledge: "Reflection noted: Had to explain memory-first pattern again"

The marker is captured in the session transcript automatically.

**Note:** Use `reflect:` (no slash). The CLI intercepts `/commands` before Kiro sees them.

## How It Works

### Discovery Phase (Index)
- Query SQLite for sessions since last analysis
- Parse transcripts (user messages start with "> ")
- Detect reflection markers and correction signals
- Build lightweight index in OpenMemory

### Validation Phase (Full Transcripts)
- Read complete sessions from SQLite for HIGH PRIORITY patterns
- Understand what you were teaching Kiro
- Verify it's a real pattern (not coincidence)

### Promotion Phase
- Craft evidence-based proposals
- You review and approve
- Kiro updates steering files

### Cleanup Phase
- Delete proposals from OpenMemory
- Regenerate index (remove promoted patterns)
- Update last analysis date
- **NO cleanup of SQLite** (Kiro manages database)

## Memory Management

Analysis metadata stored in OpenMemory:
- `interaction-analysis-state`: Last analysis date, snooze
- `interaction-analysis-index`: Pattern counts, session IDs
- `interaction-analysis-proposal`: Pending proposals
- `interaction-analysis-promoted`: Promotion tracking
- `interaction-analysis-validation`: Effectiveness metrics

Session transcripts stay in SQLite permanently (Kiro manages this).

## Confidence Building

Track improvement over time:
- **Week 2**: Baseline (e.g., 23% correction rate)
- **Week 4**: First promotions, track improvement
- **Week 6**: Review metrics, celebrate wins
- **Week 8**: Assess overall improvement

The goal: Fewer corrections over time as Kiro learns your patterns.

## Files

- `SKILL.md` - Skill logic (for Kiro)
- `README.md` - This file (for you)

## Integration

This skill integrates with:
- `15-interaction-logging.md` - Defines what to log
- `09-memory-lifecycle.md` - Steering file lifecycle
- SQLite database - Stores session transcripts
- OpenMemory - Stores analysis metadata
- Personal steering files - Where patterns get promoted

## Tips

1. **Use reflect: for important moments** - Don't wait for automatic detection
2. **Run analysis weekly** - Keeps patterns fresh
3. **Be honest in reviews** - Reject false patterns, refine unclear ones
4. **Track improvement** - Celebrate when corrections decrease
5. **Evolve the system** - Adjust thresholds, add new correction types

## Troubleshooting

**"No patterns found"**
- You might not have enough flagged interactions yet (need 10+)
- Try using reflect: more to flag important moments

**"Too many false positives"**
- Adjust threshold in SKILL.md (maybe 4+ instead of 3+)
- Be more selective in reviews (reject patterns that aren't real)

**"Promoted pattern didn't help"**
- The rule might be too vague or incomplete
- Refine the wording to be more specific
- Track effectiveness and iterate

## Version Control

This skill is version controlled in your nixos-config:
- Source: `~/Documents/projects/nixos-config/home/caubut/features/cli/code/kiro/kiro-config/skills/interaction-analysis/`
- Symlinked to: `~/.kiro/skills/interaction-analysis/`
- Edit source files, changes propagate immediately (no rebuild needed)

## Future Enhancements

As you use this skill, you might want to:
- Add new correction types (discover as you go)
- Adjust confidence thresholds (2 vs 3 occurrences)
- Add workspace-specific analysis (separate personal vs project patterns)
- Track more metrics (task completion time, first-try success rate)

This is always evolving - adapt it to your needs!
