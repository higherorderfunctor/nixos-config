{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  system.stateVersion = "24.05";

  imports = [
    ../../modules/nixos/disk-config.nix
  ];
}
