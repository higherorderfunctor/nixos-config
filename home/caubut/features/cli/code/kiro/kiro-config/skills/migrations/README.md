# Agent Skills Migration Guides

This directory contains migration guides for agent skill transitions.

## Purpose

When agent skills change significantly (methodology, input/output format, integration), document the migration here.

## When to Create a Migration Guide

Create a guide when:
- Changing analysis methodology (e.g., new pattern detection algorithm)
- Adding/removing major features (e.g., new analysis phase)
- Modifying input/output format (e.g., different proposal structure)
- Integration changes (e.g., new steering file dependencies)

For minor refinements (clarifications, examples, bug fixes), update the skill in place.

## Migration Guide Template

```markdown
# Migration: [Old Approach] → [New Approach] (YYYY-MM)

## Why This Change

- Reason 1
- Reason 2

## Old Behavior

\`\`\`
Description of old skill behavior
\`\`\`

## New Behavior

\`\`\`
Description of new skill behavior
\`\`\`

## Migration Steps

1. Step 1
2. Step 2

## Timeline

- **Start**: YYYY-MM-DD
- **Complete**: YYYY-MM-DD
- **Verification**: How to verify migration is complete

## Impact

- What changes for users
- What changes for Kiro
- Backward compatibility notes
```

## Naming Convention

Use format: `YYYY-MM-description.md`

Examples:
- `2026-03-interaction-analysis-skill.md` (initial creation)
- `2026-04-add-workspace-filtering.md` (feature addition)
- `2026-05-change-threshold-logic.md` (methodology change)

## Lifecycle

1. **Active**: Migration guide created, skill being updated
2. **Complete**: Migration finished, skill verified working
3. **Archived**: After 3+ months, compress to 09-memory-lifecycle.md reference

## Examples

_No migration guides yet. This will be populated as skills evolve._
