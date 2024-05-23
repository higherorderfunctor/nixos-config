{
  config,
  inputs,
  lib,
  outputs,
  ...
}: {
  imports =
    [
      inputs.home-manager.nixosModules.home-manager
      ./impermanence.nix
      ./mutable-users.nix
      ./nix.nix
      ./nvim.nix
      ./sops.nix
      ./zsh.nix
      ../users/caubut
    ]
    ++ (builtins.attrValues outputs.nixosModules);

  # home manager
  home-manager = {
    useGlobalPkgs = true;
    useUserPackages = true;
    backupFileExtension = "backup";
    extraSpecialArgs = {
      inherit inputs outputs;
    };
  };

  # pin state version
  system = import ./state-version.nix;

  # disable root
  users.users.root.hashedPassword = "!";

  # bootloader
  boot = {
    loader = {
      systemd-boot = {
        enable = true;
        consoleMode = "max";
        configurationLimit = 64;
      };
      efi.canTouchEfiVariables = true;
    };
    kernel = {
      sysctl = {
        "fs.inotify.max_queued_events" = "524288";
        "fs.inotify.max_user_watches" = "524288";
      };
    };
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
    #useDHCP = lib.mkDefault true;
    networkmanager.enable = true;
  };

  # https://nixos.wiki/wiki/Fwupd
  services.fwupd.enable = true;
  hardware.enableAllFirmware = lib.mkDefault true;

  # security
  security.sudo = {
    execWheelOnly = true;
    extraConfig = ''
      Defaults lecture="never"
    '';
  };

  # configure for sops even if openssh is not enabled
  services.openssh = {
    hostKeys = [
      {
        # must be a persisted path since sops runs before impermanence
        path = "/persist/etc/ssh/ssh_host_ed25519_key";
        type = "ed25519";
      }
    ];
  };

  environment.etc = {
    "ssh/ssh_host_ed25519_key.pub".source = ../../${config.networking.hostName}/secrets/ssh_host_ed25519_key.pub;
  };
}
