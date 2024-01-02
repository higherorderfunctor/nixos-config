{lib, ...}: {
  imports = [
    ./nix.nix
    ./sops.nix
    ./zsh.nix
    ../users/caubut
  ];

  # system state version
  system.stateVersion = "24.05";

  # disable root
  users.users.root.hashedPassword = "!";

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

  # set locales
  i18n = {
    defaultLocale = lib.mkDefault "en_US.UTF-8";
    supportedLocales = lib.mkDefault [
      "en_US.UTF-8/UTF-8"
    ];
  };

  # networking
  networking = {
    useDHCP = true;
  };
}
