{
  config,
  lib,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
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
  xdg.configFile.nvim.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-config";

  xdg.dataFile = {
    "nvim/lazy/nvim-treesitter/parser/cql.so".source = "${pkgs.tree-sitter-grammars.tree-sitter-cql}/parser";
    "nvim/lazy/nvim-treesitter/queries/cql".source =
      config.lib.file.mkOutOfStoreSymlink
      "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-runtime/nvim-treesitter/queries/cql";
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
    ];
  };
}
