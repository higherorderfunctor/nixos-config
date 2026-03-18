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

  # ── git-analytics MCP server ───────────────────────────────────
  git-analytics-mcp-server = pkgs.buildNpmPackage {
    pname = "git-analytics-mcp-server";
    version = "1.0.0";
    src = pkgs.fetchFromGitHub {
      owner = "singhashish4000";
      repo = "MCP-Server";
      rev = "d531a4b7d4b5a01d5fda48267e61a23af80d220d";
      hash = "sha256-RzdXO1VQHYQsK039+hs3BleQl6ISc4wQoc59QMCd29c=";
    };
    npmDepsHash = "sha256-Fa3TjwUW0uoUnKV5JSvDc+44i/4ssL3xWmRuIO40064=";
    buildPhase = ''
      runHook preBuild
      npx tsc
      # Fix: console.log pollutes stdout (MCP protocol channel)
      sed -i 's/console\.log/console.error/g' dist/*.js
      runHook postBuild
    '';
    installPhase = ''
      runHook preInstall
      mkdir -p $out/lib/git-analytics-mcp-server
      cp -r dist node_modules package.json $out/lib/git-analytics-mcp-server/
      runHook postInstall
    '';
  };

  # ── Symlink helper ────────────────────────────────────────────
  # Generates mkOutOfStoreSymlink entries for a directory of files.
  # Avoids repeating the same pattern 11 times.

  kiroConfigPath = "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/code/kiro/kiro-config";
  # ↑ IMPORTANT: adjust this to the actual absolute path to your module

  kiroCortexPath = "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/code/kiro/kiro-cortex";

  symlinkSteering = name: {
    ".kiro/steering/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/steering/${name}";
  };

  symlinkAgent = name: {
    ".kiro/agents/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/agents/${name}";
  };

  symlinkAgentDir = name: {
    ".kiro/agents/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/agents/${name}";
  };

  symlinkSkill = name: {
    ".kiro/skills/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/skills/${name}";
  };

  symlinkSetting = name: {
    ".kiro/settings/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${kiroConfigPath}/settings/${name}";
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
    "meta-workflow.json"
  ];

  # Directories under agents/ that need symlinks (e.g., prompts/)
  agentDirs = [
    "prompts"
  ];

  skillDirs = [
    "interaction-analysis"
  ];

  settingFiles = [
    "cli.json"
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
          OM_METADATA_BACKEND = "postgres";
          OM_VECTOR_BACKEND = "postgres";
          OM_PG_HOST = "localhost";
          OM_PG_PORT = "5435";
          OM_PG_DB = "openmemory";
          OM_PG_USER = "${username}";
          OM_PG_PASSWORD = "";
          OM_PG_SSL = "disable";
          OM_EMBEDDINGS = "ollama";
          OM_OLLAMA_URL = "http://localhost:11434";
          OM_OLLAMA_MODEL = "nomic-embed-text";
          OM_VEC_DIM = "768";
          OM_TIER = "deep";
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
        command = "${pkgs.mcp-server-fetch}/bin/mcp-server-fetch";
        args = [];
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
      kiro-cortex = {
        command = "${pkgs.bun}/bin/bun";
        args = ["run" "${kiroCortexPath}/agents/meta-workflow/src/main.ts"];
        env = {
          CORTEX_DEBUG = "true";
        };
      };
      git-analytics = {
        command = "${pkgs.nodejs}/bin/node";
        args = ["${git-analytics-mcp-server}/lib/git-analytics-mcp-server/dist/index.js"];
      };
    };
  };
  # ── Default agent configuration ────────────────────────────────
  defaultAgentConfig = {
    name = "default";
    description = "Default agent with curated tool permissions";
    model = "claude-opus-4.6";
    tools = ["*"];
    inherit (mcpConfig) mcpServers;
    allowedTools = [
      "fs_read"
      "grep"
      "glob"
      "introspect"
      "code"
      "sequentialthinking"
      "@openmemory"
      "@git/git_status"
      "@git/git_log"
      "@git/git_diff"
      "@git/git_diff_staged"
      "@git/git_diff_unstaged"
      "@git/git_show"
      "@git/git_branch"
      "@git-analytics"
      "@github/get_code_scanning_alert"
      "@github/get_commit"
      "@github/get_file_contents"
      "@github/get_label"
      "@github/get_latest_release"
      "@github/get_release_by_tag"
      "@github/get_tag"
      "@github/issue_read"
      "@github/list_*"
      "@github/search_*"
      "@aws-knowledge"
      "@context7"
      "@effect-docs"
      "@nixos"
      "@kiro-cortex"
      "@sequential-thinking"
    ];
    toolsSettings = {
      execute_bash = {
        autoAllowReadonly = true;
        allowedCommands = [
          "readlink -f .*"
          "ollama list.*"
          "systemctl --user status .*"
          "curl http://localhost:.*"
        ];
      };
      use_aws = {
        autoAllowReadonly = true;
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
      bun
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
        ".kiro/agents/default.json".text = builtins.toJSON defaultAgentConfig;
      }
      # Steering files (out-of-store symlinks — edit without rebuild)
      // builtins.foldl' (acc: name: acc // symlinkSteering name) {} steeringFiles
      # Agent files (out-of-store symlinks)
      // builtins.foldl' (acc: name: acc // symlinkAgent name) {} agentFiles
      # Agent directories (out-of-store symlinks, e.g., prompts/)
      // builtins.foldl' (acc: name: acc // symlinkAgentDir name) {} agentDirs
      # Skill directories (out-of-store symlinks)
      // builtins.foldl' (acc: name: acc // symlinkSkill name) {} skillDirs
      # Settings files (out-of-store symlinks — edit without rebuild)
      // builtins.foldl' (acc: name: acc // symlinkSetting name) {} settingFiles;
  };

  # ── kiro-cortex: OPA user service ────────────────────────
  systemd.user.services.kiro-cortex-opa = {
    Unit = {
      Description = "kiro-cortex Open Policy Agent";
      After = ["default.target"];
    };
    Service = {
      Type = "simple";
      ExecStart = "${pkgs.open-policy-agent}/bin/opa run --server --addr localhost:8181 --bundle ${kiroCortexPath}/policies";
      Restart = "on-failure";
    };
    Install.WantedBy = ["default.target"];
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
      ExecStartPost = pkgs.writeShellScript "db-init" ''
        for i in $(seq 1 30); do
          ${pgWithExtensions}/bin/pg_isready -h localhost -p 5435 -q && break
          sleep 1
        done
        ${pgWithExtensions}/bin/createdb -h localhost -p 5435 kiro_cortex 2>/dev/null || true
        ${pgWithExtensions}/bin/createdb -h localhost -p 5435 openmemory 2>/dev/null || true

        # Pre-create pgvector extension and vectors table with explicit dimension.
        # OpenMemory db.ts creates "v vector" (no dimension) then tries HNSW index
        # which requires fixed dimensions — upstream bug workaround.
        ${pgWithExtensions}/bin/psql -h localhost -p 5435 -d openmemory -c "
          CREATE EXTENSION IF NOT EXISTS vector;
          CREATE TABLE IF NOT EXISTS openmemory_vectors(
            id uuid, sector text, user_id text,
            v vector(768), dim integer NOT NULL,
            PRIMARY KEY(id, sector)
          );
        "
      '';
      Restart = "on-failure";
    };
    Install.WantedBy = ["default.target"];
  };
}
