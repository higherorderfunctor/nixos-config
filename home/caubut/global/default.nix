{
  config,
  inputs,
  lib,
  ...
}: {
  imports = [
    inputs.impermanence.nixosModules.home-manager.impermanence
    inputs.sops-nix.homeManagerModules.sops
    ../features/cli
    ../features/cli/starship.nix
    ../features/colors/catppuccin-mocha.nix
    ../features/neovim
  ];

  # TODO: not needed with global pkgs?
  # nixpkgs = {
  #   overlays = [
  #     inputs.neovim-nightly-overlay.overlay
  #   ];
  #   config = {
  #     allowUnfree = true;
  #   };
  # };

  systemd.user.startServices = "sd-switch";

  programs = {
    home-manager.enable = true;
  };

  xdg = {
    enable = true;
    userDirs = {
      enable = true;
      createDirectories = true;
    };
  };

  # secrets
  sops = {
    defaultSopsFile = ../secrets/secrets.yaml;
    secrets = {
      "${config.home.username}-secret-key" = {
        path = "${config.home.homeDirectory}/.ssh/id_ed25519";
        mode = "600";
      };
    };
  };

  home =
    # lock system and home-mnager state versions
    (import ../../../hosts/common/global/state-version.nix)
    // {
      username = lib.mkDefault "caubut";
      homeDirectory = lib.mkDefault "/home/${config.home.username}";

      persistence = {
        "/persist/home/caubut" = {
          directories = [
            {
              directory = ".ssh";
              mode = "700";
            }
            "Documents"
            "Downloads"
            "Pictures"
            "Videos"
          ];
          files = [
            {
              file = ".ssh/known_hosts";
              mode = "600";
            }
          ];
          allowOther = true;
        };
      };
      file."id_ed25519.pub" = {
        source = ../secrets/id_ed25519.pub;
        target = "${config.home.homeDirectory}/.ssh/id_ed25519.pub";
        mode = "644";
      };
      # file."Documents.personal.nixos-config" = {
      #   source = inputs.self.outPath;
      #   recursive = true;
      # };
    };
}
