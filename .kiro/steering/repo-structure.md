# Repository Structure

This repository manages personal Kiro configuration through NixOS/Home Manager. The kiro-config directory is symlinked to `~/.kiro/` for live editing without rebuilds.

## Directory Mapping

Home Manager creates out-of-store symlinks during activation:

```
home/caubut/features/cli/code/kiro/kiro-config/steering/
  → ~/.kiro/steering/

home/caubut/features/cli/code/kiro/kiro-config/agents/
  → ~/.kiro/agents/

home/caubut/features/cli/code/kiro/default.nix
  → generates ~/.kiro/settings/mcp.json (inline, not symlinked)
```

## Editing Workflow

1. **Edit source files** in `kiro-config/steering/` or `kiro-config/agents/`
2. **Changes are immediate** — symlinks mean no rebuild needed
3. **Test** the changes in a Kiro session
4. **Commit** when satisfied

No `home-manager switch` required for steering/agent changes. Only needed when modifying MCP server configuration in `default.nix`.

## Secrets Management

API keys are managed via nix-sops and injected at runtime:

- **Kagi API key**: `sops.secrets."${username}-kagi-api-key"` → wrapper script reads at runtime
- **GitHub PAT**: `sops.secrets."${username}-github-api-key"` → wrapper script reads at runtime
- **AWS credentials**: Uses existing `~/.aws/` profiles, no secrets in Nix

Wrapper scripts (`kagiWrapper`, `githubWrapper`, `awsMcpWrapper`) read decrypted secrets and export as environment variables before executing the MCP server.

**Never hardcode secrets** in `default.nix` or any config file. Always use sops-managed secrets with runtime injection.

## What NOT to Do

**Don't edit `~/.kiro/` directly:**
- Changes to symlinked files (steering, agents) will persist but won't be tracked in git
- Changes to generated files (mcp.json) will be overwritten on next activation
- Always edit the source in `kiro-config/`

**Don't commit secrets:**
- API keys belong in sops-encrypted files, not in Nix expressions
- Use wrapper scripts for runtime injection

**Don't add workspace-specific steering here:**
- This repo contains PERSONAL global configuration only
- Workspace steering belongs in the workspace's `.kiro/steering/` directory
- Personal steering (00-11) defines the framework; workspace steering specializes it

## Scope

This configuration is:
- **Personal**: Applies to user "caubut" across all workspaces
- **Global**: Defines how Kiro operates, not project-specific conventions
- **Portable**: Can be deployed to any machine via NixOS/Home Manager

Workspace-specific conventions, patterns, and domain rules belong in each workspace's `.kiro/` directory, not here.
