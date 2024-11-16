{
  config,
  inputs,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  imports = [inputs.ags.homeManagerModules.default];

  programs.ags = {
    enable = true;

    extraPackages = [
      inputs.ags.packages.${pkgs.system}.apps
      inputs.ags.packages.${pkgs.system}.battery
      inputs.ags.packages.${pkgs.system}.hyprland
      inputs.ags.packages.${pkgs.system}.mpris
      inputs.ags.packages.${pkgs.system}.network
      inputs.ags.packages.${pkgs.system}.tray
      inputs.ags.packages.${pkgs.system}.wireplumber
    ];
  };

  # symlink to clone of project to allow for easy editing
  xdg.configFile.ags.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/desktop/ags/ags-config2";
}
