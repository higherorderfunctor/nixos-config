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

  # TODO: # secrets
  # sops = {
  #   defaultSopsFile = ../secrets/secrets.yaml;
  #   secrets = {
  #     "${config.home.username}-secret-key" = {
  #       path = "${config.home.homeDirectory}/.ssh/id_ed25519";
  #       mode = "600";
  #     };
  #   };
  # };

  home =
    # lock system and home-mnager state versions
    (import ../../../hosts/common/global/state-version.nix)
    // {
      username = "caubut";
      homeDirectory = "/home/${config.home.username}";
      persistence = {
        "/persist/home/caubut" = {
          directories = [
            "Documents"
            "Downloads"
            "Pictures"
            "Videos"
          ];
          files = [
            ".ssh/known_hosts"
          ];
          allowOther = true;
        };
      };
      file = {
        ".ssh/id_ed25519".source = config.lib.file.mkOutOfStoreSymlink "/run/secrets/caubut-secret-key";
        ".ssh/id_ed25519.pub".source = ../secrets/id_ed25519.pub;
      };
    };
}
