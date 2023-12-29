{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  system.stateVersion = "24.05";

  imports = [
    ../../modules/nixos
  ];

  # bootloader
  boot = {
    loader = {
      systemd-boot = {
        enable = true;
        configurationLimit = 42;
      };
      efi = {
        canTouchEfiVariables = true;
      };
    };
  };

  # timezone
  time.timeZone = "America/Denver";
}
