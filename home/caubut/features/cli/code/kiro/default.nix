{
  config,
  pkgs,
  ...
}: let
  username = "${config.home.username}";

  # ── kiro-cortex: PostgreSQL 18 + pgvector ─────────────────────
  pgWithExtensions = pkgs.postgresql_18.withPackages (p: [p.pgvector]);
  pgDataDir = "${config.xdg.dataHome}/kiro-cortex/postgresql";

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

  awsMcpWrapper = pkgs.writeShellScript "aws-mcp" ''
    # Use existing AWS_PROFILE if set, otherwise detect first available profile
    if [ -z "$AWS_PROFILE" ]; then
      DETECTED_PROFILE=$(${pkgs.awscli2}/bin/aws configure list-profiles 2>/dev/null | head -1)
      if [ -z "$DETECTED_PROFILE" ]; then
        exit 1
      fi
      export AWS_PROFILE="$DETECTED_PROFILE"
    fi

    # Verify credentials are actually valid (handles expired SSO sessions)
    if ! ${pkgs.awscli2}/bin/aws sts get-caller-identity --profile "$AWS_PROFILE" >/dev/null 2>&1; then
      echo "AWS credentials for profile $AWS_PROFILE are expired or invalid" >&2
      echo "Run: aws sso login --profile $AWS_PROFILE" >&2
      exit 1
    fi

    exec ${pkgs.nodejs}/bin/npx -y mcp-remote \
      "https://mcp.us-east-1.amazonaws.com/sse" "$@"
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

  symlinkSkill = name: {
    ".kiro/skills/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/skills/${name}";
  };

  # ── Steering file list ────────────────────────────────────────
  steeringFiles = [
    "00-ip-protection.md"
    "01-tool-usage.md"
    "02-research-depth.md"
    "03-sequential-thinking.md"
    "04-git.md"
    "05-context7.md"
    "06-search.md"
    "07-github.md"
    "08-memory.md"
    "09-memory-lifecycle.md"
    "10-self-awareness.md"
    "11-provenance-heuristics.md"
    "12-thinking-depth.md"
    "13-ideation-workflow.md"
    "14-ollama-models.md"
    "15-interaction-logging.md"
  ];

  agentFiles = [
    "ideation.json"
  ];

  skillDirs = [
    "interaction-analysis"
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
          OM_EMBEDDINGS = "ollama";
          OM_OLLAMA_URL = "http://localhost:11434";
          OM_OLLAMA_MODEL = "nomic-embed-text";
          OM_VEC_DIM = "768";
          OM_TIER = "smart";
          # Disable forced summarization to prevent content truncation
          OM_USE_SUMMARY_ONLY = "false";
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
      effect-docs = {
        command = "npx";
        args = ["-y" "effect-mcp@latest"];
      };
      nixos = {
        command = "${pkgs.uv}/bin/uvx";
        args = ["mcp-nixos"];
      };
      aws-knowledge = {
        url = "https://knowledge-mcp.global.api.aws";
        type = "http";
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
      open-policy-agent
      pgWithExtensions
    ];

    # ── Ensure openmemory directory exists ────────────────────────
    activation.createOpenMemoryDir = config.lib.dag.entryAfter ["writeBoundary"] ''
      mkdir -p ${config.xdg.dataHome}/openmemory
    '';

    # ── Ensure kiro-cortex PostgreSQL data dir exists ─────────────
    activation.createCortexPgDir = config.lib.dag.entryAfter ["writeBoundary"] ''
      mkdir -p ${pgDataDir}
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
      // builtins.foldl' (acc: name: acc // symlinkAgent name) {} agentFiles
      # Skill directories (out-of-store symlinks)
      // builtins.foldl' (acc: name: acc // symlinkSkill name) {} skillDirs;
  };

  # ── kiro-cortex: PostgreSQL user service ────────────────────────
  systemd.user.services.kiro-cortex-postgresql = {
    Unit = {
      Description = "kiro-cortex PostgreSQL 18";
      After = ["default.target"];
    };
    Service = {
      Type = "simple";
      ExecStartPre = pkgs.writeShellScript "pg-init" ''
        if [ ! -f "${pgDataDir}/PG_VERSION" ]; then
          ${pgWithExtensions}/bin/initdb -D "${pgDataDir}" --no-locale --encoding=UTF8
        fi
      '';
      ExecStart = "${pgWithExtensions}/bin/postgres -D ${pgDataDir} -k /tmp -h localhost -p 5435";
      Restart = "on-failure";
    };
    Install.WantedBy = ["default.target"];
  };
}
