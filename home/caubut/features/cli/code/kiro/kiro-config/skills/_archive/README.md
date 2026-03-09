# Archived Agent Skills

This directory contains agent skills that are no longer active. Preserved for historical reference.

## Archive Index

_No archived skills yet. This will be populated as skills are deprecated._

## When to Archive

A skill should be archived when:

1. The skill is fully replaced by a better approach
2. The skill is no longer needed (3+ months unused)
3. Functionality has moved elsewhere
4. Verified obsolete across all use cases

## Archive Format

Each archived skill directory should include metadata at the top of SKILL.md:

```markdown
---
archived: YYYY-MM-DD
reason: "Brief explanation"
replacement: "path/to/new/skill or 'none'"
last_used: YYYY-MM-DD
verification: "How we verified it's no longer needed"
---
```

## Accessing Archived Content

Archived skills are searchable via git and can be referenced when needed for:

- Understanding historical decisions
- Reviving deprecated approaches if needed
- Audit and compliance purposes
- Institutional knowledge preservation

## Compression to Steering

After 1-2 years, archived skills may be compressed into the "Historical Skills" section of 09-memory-lifecycle.md with:

- Brief summary of the skill
- Reason for deprecation
- Archival date
- Link to full archived directory (if needed)

This keeps the archive directory focused on recent history while preserving searchability.
