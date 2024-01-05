{
  inputs,
  lib,
  outputs,
  ...
}: {
  imports = [
    inputs.home-manager.nixosModules.home-manager
    ./impermanence.nix
    ./mutable-users.nix
    ./nix.nix
    ./neovim.nix
    ./sops.nix
    ./zsh.nix
    ../users/caubut
  ];

  # nixpkgs
  nixpkgs = {
    config = {
      allowUnfree = true;
    };
  };

  # home manager
  home-manager = {
    useGlobalPkgs = true;
    useUserPackages = true;
    extraSpecialArgs = {inherit inputs outputs;};
  };

  # system state version
  system = import ./state-version.nix;

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
