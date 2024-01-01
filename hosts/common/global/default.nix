{inputs, ...}: {
  imports = [
    ./nix.nix
    ./shell.nix
    ./sops.nix
    ../users/caubut
  ];

  # system state version
  system.stateVersion = "24.05";

  # bootloader
  boot.loader = {
    systemd-boot = {
      enable = true;
      consoleMode = "max";
      configurationLimit = 64;
    };
    efi.canTouchEfiVariables = true;
  };

  # timezone
  time.timeZone = "America/Denver";

  # networking
  networking = {
    useDHCP = true;
  };
}
