---
name: secrets-private-repo
description: Secrets and identity live in a private Codeberg flake input (nixos-secrets)
type: project
---

All sops-encrypted secrets, public keys, and identity config (emails, usernames,
SSH hosts) are in a private Codeberg repo consumed as a flake input. The public
nixos-config repo contains no identity info or secret key names.

Editing workflow: clone private repo, `sops edit`, push, then
`nix flake lock --update-input nixos-secrets` in nixos-config.
