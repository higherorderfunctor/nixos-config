{
  lib,
  pkgs,
  ...
}: {
  imports = [
    ../../global
    ../../features/cli/nix.nix
    ../../features/system/nix-gl-host.nix
    ../../features/desktop
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
  # fix for non-nixos systems
  targets.genericLinux.enable = true;

  # TODO:
  home.packages = [pkgs.gnome-network-displays];
}
