---
name: claude-config-via-nixos
description: Never write directly to ~/.claude/ — all config is managed via outOfStoreSymlinks in nixos-config repo
type: feedback
---

Never write directly to `~/.claude/`. All claude config (settings.json, CLAUDE.md,
project memory, etc.) is managed via NixOS home-manager outOfStoreSymlinks.

**Why:** User manages all dotfiles declaratively through nixos-config for
portability and reproducibility. Direct writes would be overwritten on rebuild
or create conflicts with symlinks.

**How to apply:** When needing to modify any file under `~/.claude/`, edit the
source at `home/<user>/features/cli/code/ai/claude/claude-config/` instead. If
a new file/directory needs to exist under `~/.claude/`, update the nix module
at `home/<user>/features/cli/code/ai/claude/default.nix` to add the symlink.
