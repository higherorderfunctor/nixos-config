{
  config,
  pkgs,
  ...
}: {
  imports = [
    ./ai
    ./docker.nix
    ./kiro
    ./markdown.nix
    ./openapi.nix
    ./yaml.nix
    ./zig.nix
  ];

  home.packages = with pkgs; [
    vscode-langservers-extracted
    # kiro-cli
    # kiro-gateway
    uv
  ];

  # home.file = {
  #   ".kiro/settings/mcp.json" = let
  #     mcpConfig = {
  #       mcpServers = {
  #         sequential-thinking = {
  #           command = "npx";
  #           args = ["-y" "@modelcontextprotocol/server-sequential-thinking"];
  #         };
  #         openmemory = {
  #           command = "npx";
  #           args = ["-y" "openmemory-js" "mcp"];
  #           env = {
  #             OM_DB_PATH = "${config.xdg.dataHome}/openmemory/memory.sqlite";
  #             OM_EMBEDDINGS = "synthetic";
  #           };
  #         };
  #         git = {
  #           command = "${pkgs.uv}/bin/uvx";
  #           args = ["mcp-server-git"];
  #         };
  #       };
  #     };
  #   in {
  #     text = builtins.toJSON mcpConfig;
  #   };

  #   ".kiro/steering/always-on-tools.md".text = ''
  #     # Tool Usage Guidelines

  #     ## Sequential Thinking
  #     When working on tasks that involve multi-step reasoning, debugging,
  #     architectural decisions, or any problem requiring structured analysis,
  #     use the `sequential-thinking` MCP tool to break down your thought
  #     process before acting.

  #     Always use sequential thinking for:
  #     - Debugging complex issues
  #     - Planning multi-file changes
  #     - Evaluating tradeoffs between approaches
  #     - Any task with more than 2 logical steps

  #     ## Git
  #     Use the `git` MCP tools for all git operations rather than raw shell
  #     commands. This includes viewing diffs, file history, commit logs,
  #     file contents at specific revisions, branches, tags, and status.

  #     Prefer the git MCP over shell `git` commands — it provides structured
  #     output that is easier to reason about.

  #     ### Git Worktree Awareness
  #     The user frequently uses **git worktrees**. Multiple working directories
  #     may point to the same repository. When determining repository identity:
  #     - Use the `git` MCP to inspect the remote origin URL
  #     - Extract the repo identifier (e.g., `git@github.com:org/repo.git` → `org/repo`)
  #     - If no remote exists, the common git dir is the stable identifier

  #     Always be aware that the current working directory may be a worktree,
  #     not the main checkout. Never assume directory name equals project name.

  #     ## Memory (OpenMemory)

  #     ### CRITICAL: Scoping Rules
  #     When using openmemory tools, ALWAYS follow these scoping rules:
  #     - **user_id**: set to "caubut" on every call
  #     - **tags**: ALWAYS include a tag for the git repository identity

  #     ### Memory Types
  #     When storing memories, use the correct `type` parameter:
  #     - `contextual` — decisions, conventions, patterns, workflow preferences
  #     - `factual` — concrete facts: names, URLs, versions, endpoints
  #     - `both` — when a memory is both a fact and provides context

  #     When in doubt, use `contextual`.

  #     ### Determining the Project Tag
  #     1. Use the `git` MCP to get the remote origin URL
  #     2. Extract the repo name (e.g., `git@github.com:org/repo.git` → `org/repo`)
  #     3. Include that as a tag when storing AND filtering when searching
  #     4. If no remote exists, use the git common directory path as the tag
  #     5. If not in a git repo, use the tag `global`

  #     ### Tag Examples
  #     - Worktree at `~/code/my-repo/` → tags: `["org/my-repo"]`
  #     - Worktree at `~/code/my-repo-feat-x/` → tags: `["org/my-repo"]` (SAME)
  #     - Non-git directory → tags: `["global"]`
  #     - Universal preferences → tags: `["global", "preferences"]`

  #     ### When to Search
  #     - **Before starting any task**, search for relevant context
  #     - Before proposing changes that might conflict with prior decisions
  #     - When the user references something from a previous session

  #     ### When to Store
  #     - Architectural decisions and their rationale (`contextual`)
  #     - Important debugging findings (`contextual`)
  #     - Project conventions and patterns (`contextual`)
  #     - API endpoints, service URLs, version pins (`factual`)
  #     - Coding style preferences and workflow patterns (`contextual`)

  #     Always check memory before proposing changes that might contradict
  #     prior decisions.

  #     ### What NOT to Store
  #     - Trivial implementation details
  #     - Temporary workarounds (unless explicitly asked)
  #     - Information already in steering files or project docs
  #   '';
  # };
}
