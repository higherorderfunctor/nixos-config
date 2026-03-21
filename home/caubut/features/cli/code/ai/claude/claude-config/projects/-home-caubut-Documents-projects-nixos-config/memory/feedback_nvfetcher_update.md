---
name: feedback_nvfetcher_update
description: Always use scripts/nix-update instead of running nvfetcher directly — it does post-processing on generated files
type: feedback
---

Use `scripts/nix-update` instead of running `nvfetcher` directly.

**Why:** The script does post-processing on the generated files that raw nvfetcher doesn't handle.

**How to apply:** When adding a new nvfetcher entry or updating packages, tell the user to run `scripts/nix-update` (or run it yourself) rather than invoking `nvfetcher` directly.
