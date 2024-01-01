{inputs, ...}: {
  imports = [
    ./nix.nix
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
    hostName = "alcyone";
    useDHCP = true;
  };
}
