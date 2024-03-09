{
  config,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    defaultEditor = true;
  };

  # symlink to clone of project to allow for easy editing
  xdg.configFile.nvim.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-config";

  # permission fixes
  systemd.user.tmpfiles.rules = [
    "z ${config.xdg.dataHome}/zsh 0700 ${username} ${username} - -"
    "z /persist${config.xdg.dataHome}/zsh 0700 ${username} ${username} - -"
    "z ${config.xdg.stateHome}/zsh 0700 ${username} ${username} - -"
    "z /persist${config.xdg.stateHome}/zsh 0700 ${username} ${username} - -"
  ];

  # persistence
  home.persistence = {
    "/persist${config.xdg.dataHome}".directories = ["nvim"];
    "/persist${config.xdg.stateHome}".directories = ["nvim"];
  };
}
