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
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.apps
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.auth
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.battery
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.bluetooth
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.cava
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.greet
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.hyprland
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.io
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.mpris
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.network
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.notifd
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.powerprofiles
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.river
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.tray
      inputs.ags.packages.${pkgs.stdenv.hostPlatform.system}.wireplumber
    ];
  };

  # symlink to clone of project to allow for easy editing
  xdg.configFile.ags.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/desktop/ags/ags-config2";
}
