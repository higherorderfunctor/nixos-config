# Migration: Personal Steering Lifecycle Implementation (2026-03)

## Why This Change

- Establish structured lifecycle for personal steering file management
- Align personal steering with workspace steering patterns (repo-analysis)
- Enable systematic tracking of workflow evolution
- Provide clear guidance for when to update vs migrate vs archive

## Old Pattern

Personal steering files updated ad-hoc without structured lifecycle:
- No distinction between minor updates and major pattern changes
- No historical tracking of deprecated patterns
- No migration guides for significant workflow changes

## New Pattern

Structured lifecycle with three states:
- **Active** - Current steering files (00-14.md)
- **migrations/** - Pattern transitions in progress or recently completed
- **_archive/** - Deprecated patterns preserved for historical reference

## Migration Steps

1. ✅ Create `migrations/README.md` with template and guidance
2. ✅ Create `_archive/README.md` with archival criteria
3. ✅ Update `09-memory-lifecycle.md` with lifecycle management rules
4. ✅ Update `10-self-awareness.md` to check migrations/_archive during bootstrap
5. ⏳ Rebuild home-manager to activate symlinks
6. ⏳ Verify lifecycle structure accessible via ~/.kiro/steering/

## Timeline

- **Start**: 2026-03-09
- **Target**: 2026-03-09 (same day)
- **Verification**: `ls -la ~/.kiro/steering/migrations/ ~/.kiro/steering/_archive/`

## Status

- [x] Infrastructure created (migrations/, _archive/)
- [x] Steering files updated (09, 10)
- [ ] Home-manager rebuild
- [ ] Verification complete

## Impact

**Files modified:**
- `09-memory-lifecycle.md` - Added "Personal Steering Lifecycle" section
- `10-self-awareness.md` - Added migrations/_archive bootstrap awareness

**Files created:**
- `migrations/README.md` - Migration guide template and criteria
- `_archive/README.md` - Archival template and criteria
- `migrations/2026-03-personal-steering-lifecycle.md` - This file (meta!)

**Behavioral changes:**
- AI now distinguishes between minor updates (in-place) and pattern changes (migration guide)
- AI checks migrations/ during bootstrap to understand what's changing
- AI can reference _archive/ for historical context
