# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

A NixOS flake managing full system and home-manager configurations. Tracks
nixos-unstable. Single user (`caubut`), multiple machines.

## Build & Deploy

```bash
# NixOS system rebuild (on NixOS machines)
sudo nixos-rebuild switch --flake .#<hostname>

# Home-manager standalone rebuild (on non-NixOS machines like the Dell laptop)
home-manager switch --flake .#caubut@precision-7760

# Format all nix files
nix fmt

# Update all dependencies (nvfetcher + flake inputs)
scripts/nix-update

# Update only nvfetcher (no flake update)
scripts/nix-update --noflake
```

**Important:** Always use `scripts/nix-update` instead of running `nvfetcher`
directly — it does post-processing on generated files (vendor hash restoration,
cargo lock staging, etc.).

## Architecture

### Flake Outputs

- **nixosConfigurations**: `beelink-ser7`, `vm`, `live-cd-minimal`, `live-cd-graphical`
- **homeConfigurations**: `caubut@z690-ud-ddr4`, `caubut@precision-7760`
- **formatter**: `alejandra`

### Directory Structure

```
hosts/                          # NixOS system configs
  common/global/                # Shared system modules (impermanence, sops, nix settings)
  common/optional/              # Opt-in system features
  <hostname>/                   # Per-machine hardware + feature selection

home/caubut/
  global/                       # Base home-manager config (always imported)
  hosts/<hostname>/             # Per-machine home feature selection
  features/
    cli/                        # Shell tools, each as a standalone .nix file
      code/ai/                  # AI CLI tools (claude, copilot, kiro)
      nvim/                     # Neovim config
      git.nix                   # Git config (branchless, delta, work includes)
      ssh.nix                   # SSH keys + host aliases
      sops.nix                  # Secrets decryption (age/sops-nix)
    desktop/                    # GUI apps + Hyprland
    colors/                     # Theming (catppuccin)

overlays/                       # Package overrides
  .nvfetcher/                   # Auto-generated sources (managed by scripts/nix-update)
  default.nix                   # Overlay registry (add new overlays here)

modules/                        # Custom NixOS and home-manager modules
```

### Overlay / nvfetcher Pattern

Packages that need to track upstream faster than nixpkgs are managed via
nvfetcher + overlays:

1. Add a source entry to `nvfetcher.toml`
2. Run `scripts/nix-update` to generate `overlays/.nvfetcher/generated.{nix,json}`
3. Create `overlays/<name>-overlay.nix` that reads from generated sources and
   calls `overrideAttrs` on the nixpkgs package
4. Register the overlay in `overlays/default.nix`

Example nvfetcher entry for a GitHub release binary:
```toml
[github-copilot-cli]
src.github = "github/copilot-cli"
src.from_pattern = "v([0-9]+\\.[0-9]+\\.[0-9]+)$"
src.exclude_regex = ".*-[0-9]+$"
src.to_pattern = "\\1"
fetch.url = "https://github.com/github/copilot-cli/releases/download/v$ver/copilot-linux-x64.tar.gz"
```

### Secrets

Managed via sops-nix with a private Codeberg flake input (`nixos-secrets`).
All encrypted secrets, public keys, identity values, and sops declarations
live in the private repo. The public repo imports it and never contains
secret key names, emails, or identity info.

- **Private repo**: `git+ssh://git@codeberg.org/lucidrevisiona/nixos-secrets.git`
- **Editing secrets**: Clone the private repo, run `sops edit` there, push,
  then `nix flake lock --update-input nixos-secrets` in this repo
- **sops-nix imports** stay in this repo (`sops.nix`, `hosts/common/global/default.nix`)
- **Secret declarations + identity config** are in private NixOS/HM modules

### Multi-Identity Git

Git is configured with conditional includes for work repos. SSH uses host
aliases for multi-key routing. All identity values (emails, hostnames, SSH
matchBlocks) are declared in the private `nixos-secrets` flake input.

### Claude Code Config

Claude Code's `~/.claude/` directory is managed via outOfStoreSymlinks.
**Never write directly to `~/.claude/`**. Source of truth is:
```
home/caubut/features/cli/code/ai/claude/claude-config/
```
Changes to symlinked files are live immediately (no rebuild needed). Adding new
files/directories to `~/.claude/` requires updating the nix module at
`home/caubut/features/cli/code/ai/claude/default.nix` and rebuilding.

When corrected on stacked workflow behavior, evaluate whether the correction
reveals a gap in the global CLAUDE.md instructions at
`claude-config/CLAUDE.md`. If generalizable, propose a targeted edit to the
source. If context-specific, save as a project memory instead.

### Impermanence

The NixOS machines use impermanence — the root filesystem is ephemeral.
Persistent state is mounted from `/persist`. Home directories list persisted
paths via `home.persistence."/persist/home/caubut".directories`.
