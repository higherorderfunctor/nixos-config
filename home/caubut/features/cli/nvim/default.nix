{
  config,
  lib,
  pkgs,
  ...
}: let
  inherit (config.home) username;
  tree-sitter-cql = pkgs.tree-sitter.buildGrammar {
    pname = "tree-sitter-cql";
    version = "2024-04-13-3";
    language = "cql";
    # src = ./tree-sitter-cql;
    src = pkgs.lib.cleanSourceWith {
      src = ./tree-sitter-cql;
      filter = name: _:
        pkgs.lib.any (pattern: pkgs.lib.strings.hasInfix pattern name)
        [
          "tree-sitter-cql/grammar.js"
          "tree-sitter-cql/queries"
        ];
    };
    generate = true;
  };
in {
  home.packages = [pkgs.tree-sitter];
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    defaultEditor = true;
    extraPackages = with pkgs; [
      # TODO:
      fswatch
      tree-sitter
    ];
  };

  # symlink to clone of project to allow for easy editing
  xdg.configFile = {
    nvim.source =
      config.lib.file.mkOutOfStoreSymlink
      "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-config";

    "tree-sitter/config.json".source =
      config.lib.file.mkOutOfStoreSymlink
      "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/tree-sitter-config.json";
  };

  xdg.dataFile = {
    "nvim/lazy/nvim-treesitter/parser/cql.so".source = "${pkgs.tree-sitter-grammars.tree-sitter-cql}/parser";
    #"nvim/lazy/nvim-treesitter/queries/cql" = "${pkgs.tree-sitter-grammars.tree-sitter-cql}/queries";
    #   # "nvim/lazy/nvim-treesitter/parser/cql.so".source = "${tree-sitter-cql}/parser";
    #   # "nvim/lazy/nvim-treesitter/queries/cql".source = "${tree-sitter-cql}/queries";
    #   #  config.lib.file.mkOutOfStoreSymlink
    #   #  "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-runtime/nvim-treesitter/queries/cql";
  };

  # permission fixes
  systemd.user.tmpfiles.rules = [
    "z ${config.xdg.dataHome}/nvim 0700 ${username} ${username} - -"
    "z /persist${config.xdg.dataHome}/nvim 0700 ${username} ${username} - -"
    "z ${config.xdg.stateHome}/nvim 0700 ${username} ${username} - -"
    "z /persist${config.xdg.stateHome}/nvim 0700 ${username} ${username} - -"
  ];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nvim")
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.stateHome}/nvim")
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/github-copilot")
    ];
  };
}
