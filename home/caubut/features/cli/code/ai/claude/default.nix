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

  # Global skill directories (symlinked to ~/.claude/skills/)
  skillDirs = [
    "stack-submit"
    "stack-fix"
    "stack-split"
    "stack-test"
  ];

  symlinkSkill = name: {
    ".claude/skills/${name}".source =
      config.lib.file.mkOutOfStoreSymlink "${claudeConfigPath}/skills/${name}";
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
    // builtins.foldl' (acc: name: acc // symlinkSkill name) {} skillDirs
    // builtins.foldl' (acc: name: acc // symlinkClaudeProject nixosConfigProjectKey name) {} nixosConfigProjectDirs;
}
