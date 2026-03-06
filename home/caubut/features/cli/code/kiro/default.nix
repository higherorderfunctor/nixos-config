{
  config,
  pkgs,
  ...
}: let
  username = "${config.home.username}";

  # ── Sops wrapper scripts ──────────────────────────────────────
  # These read API keys from sops-decrypted files at runtime,
  # export them as env vars, then exec the real MCP server.

  kagiWrapper = pkgs.writeShellScript "kagi-mcp" ''
    export KAGI_API_KEY=$(cat ${config.sops.secrets."${username}-kagi-api-key".path})
    exec ${pkgs.uv}/bin/uvx kagimcp "$@"
  '';

  githubWrapper = pkgs.writeShellScript "github-mcp" ''
    export GITHUB_PERSONAL_ACCESS_TOKEN=$(cat ${config.sops.secrets."${username}-github-api-key".path})
    export GITHUB_TOOLSETS="repos,issues,code_security"
    exec ${pkgs.github-mcp-server}/bin/github-mcp-server stdio "$@"
  '';

  # ── Symlink helper ────────────────────────────────────────────
  # Generates mkOutOfStoreSymlink entries for a directory of files.
  # Avoids repeating the same pattern 11 times.

  kiroConfigPath = "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/code/kiro/kiro-config";
  # ↑ IMPORTANT: adjust this to the actual absolute path to your module

  symlinkSteering = name: {
    ".kiro/steering/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/steering/${name}";
  };

  symlinkAgent = name: {
    ".kiro/agents/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/agents/${name}";
  };

  # ── Steering file list ────────────────────────────────────────
  steeringFiles = [
    "00-ip-protection.md"
    "01-research-depth.md"
    "02-sequential-thinking.md"
    "03-git.md"
    "04-context7.md"
    "05-search.md"
    "06-github.md"
    "07-memory.md"
    "08-memory-lifecycle.md"
    "09-self-awareness.md"
  ];

  agentFiles = [
    "code-reviewer.md"
  ];

  # ── MCP configuration ────────────────────────────────────────
  mcpConfig = {
    mcpServers = {
      sequential-thinking = {
        command = "npx";
        args = ["-y" "@modelcontextprotocol/server-sequential-thinking"];
      };
      openmemory = {
        command = "npx";
        args = ["-y" "openmemory-js" "mcp"];
        env = {
          OM_DB_PATH = "${config.xdg.dataHome}/openmemory/memory.sqlite";
          OM_EMBEDDINGS = "synthetic";
        };
      };
      git = {
        command = "${pkgs.uv}/bin/uvx";
        args = ["mcp-server-git"];
      };
      context7 = {
        command = "npx";
        args = ["-y" "@upstash/context7-mcp@latest"];
      };
      kagi = {
        command = "${kagiWrapper}";
        args = [];
      };
      fetch = {
        command = "${pkgs.uv}/bin/uvx";
        args = ["mcp-server-fetch"];
      };
      github = {
        command = "${githubWrapper}";
        args = [];
      };
    };
  };
in {
  # ── Sops secrets ──────────────────────────────────────────────
  sops.secrets = {
    "${username}-kagi-api-key" = {
      mode = "0400";
    };
  };

  home = {
    packages = with pkgs; [
      kiro-cli
      kiro-gateway
      github-mcp-server
    ];

    # ── Ensure openmemory directory exists ────────────────────────
    activation.createOpenMemoryDir = config.lib.dag.entryAfter ["writeBoundary"] ''
      mkdir -p ${config.xdg.dataHome}/openmemory
    '';

    # ── File declarations ─────────────────────────────────────────
    file =
      # MCP config (inline JSON — needs Nix interpolation, rarely changes)
      {
        ".kiro/settings/mcp.json".text = builtins.toJSON mcpConfig;
      }
      # Steering files (out-of-store symlinks — edit without rebuild)
      // builtins.foldl' (acc: name: acc // symlinkSteering name) {} steeringFiles
      # Agent files (out-of-store symlinks)
      // builtins.foldl' (acc: name: acc // symlinkAgent name) {} agentFiles;
  };
}
