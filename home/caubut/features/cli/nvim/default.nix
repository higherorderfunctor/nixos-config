{
  config,
  lib,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  # TODO move some of these to system
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    defaultEditor = true;
  };
  # symlink to clone of project to allow for easy editing
  xdg.configFile.nvim.source =
    config.lib.file.mkOutOfStoreSymlink
    #"${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/neovim/nvim-config";
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/cli/nvim/nvim-config";
  # persistence
  # home.persistence = {
  #   "/persist${config.home.homeDirectory}".directories = [
  #     (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nvim")
  #     (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.stateHome}/nvim")
  #   ];
  # };
}
