{config, ...}: let
  inherit (config.home) username;

  claudeConfigPath = "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/code/ai/claude/claude-config";

  # Project memory/config directories keyed by encoded working directory path.
  # These are machine-specific but still managed in the repo for portability.
  nixosConfigProjectKey = "-home-${username}-Documents-projects-nixos-config";

  symlinkClaudeConfig = name: {
    ".claude/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${claudeConfigPath}/${name}";
  };

  symlinkClaudeProject = projectKey: name: {
    ".claude/projects/${projectKey}/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${claudeConfigPath}/projects/${projectKey}/${name}";
  };

  # Global config files (symlinked to ~/.claude/)
  configFiles = [
    "settings.json"
    "CLAUDE.md"
  ];

  # Global directories (symlinked as whole dirs to ~/.claude/<name>/)
  # New files appear automatically without rebuild.
  globalDirs = [
    "references"
    "skills"
  ];

  symlinkGlobalDir = name: {
    ".claude/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${claudeConfigPath}/${name}";
  };

  # Per-project directories (symlinked to ~/.claude/projects/<key>/)
  nixosConfigProjectDirs = [
    "memory"
  ];
in {
  programs.claude-code = {
    enable = true;
  };

  home.file =
    builtins.foldl' (acc: name: acc // symlinkClaudeConfig name) {} configFiles
    // builtins.foldl' (acc: name: acc // symlinkGlobalDir name) {} globalDirs
    // builtins.foldl' (acc: name: acc // symlinkClaudeProject nixosConfigProjectKey name) {} nixosConfigProjectDirs;
}
