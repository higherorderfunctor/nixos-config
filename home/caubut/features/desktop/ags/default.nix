{
  config,
  inputs,
  ...
}: let
  inherit (config.home) username;
in {
  imports = [inputs.ags.homeManagerModules.default];

  programs.ags = {
    enable = true;
    # additional packages to add to gjs's runtime
    #extraPackages = [pkgs.libsoup_3];
  };

  # symlink to clone of project to allow for easy editing
  xdg.configFile.ags.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/desktop/ags/take2";
  #  xdg.configFile.ags = lib.mkForce {
  #    source = ./ags-config;
  #    recursive = true;
  #  };
}
