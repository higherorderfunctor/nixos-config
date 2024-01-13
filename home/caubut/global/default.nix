{
  config,
  inputs,
  specialArgs,
  ...
}: let
  inherit (specialArgs) hostname;
  username = "caubut";
in {
  imports = [
    inputs.impermanence.nixosModules.home-manager.impermanence
    inputs.sops-nix.homeManagerModules.sops
    ../features/cli
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
    oh-my-posh.enable = true;
    # starship.enable = true;
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

  # permission fixes
  systemd.user.tmpfiles.rules = [
    "z /home/${username}/.ssh 0700 ${username} ${username} - -"
    "z /persist/home/${username}/.ssh 0700 ${username} ${username} - -"
    "z /home/${username}/.local 0700 ${username} ${username} - -"
    "z /persist/home/${username}/.local 0700 ${username} ${username} - -"
    "z /home/${username}/.local/share 0700 ${username} ${username} - -"
    "z /persist/home/${username}/.local/share 0700 ${username} ${username} - -"
  ];

  home =
    # lock system and home-mnager state versions
    {
      inherit (import ../../../hosts/common/global/state-version.nix) stateVersion;
      inherit username;
      sessionVariables = {
        NIXOS_HOST = hostname;
      };
      homeDirectory = "/home/${username}";
      persistence = {
        "/persist/home/${username}" = {
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
        ".ssh/id_ed25519".source = config.lib.file.mkOutOfStoreSymlink "/run/secrets/${username}-secret-key";
        ".ssh/id_ed25519.pub".source = ../secrets/id_ed25519.pub;
      };
      activation = {
        nixos-config = inputs.home-manager.lib.hm.dag.entryAfter ["installPackages"] ''
          if [ ! -d "${config.xdg.userDirs.documents}/projects/nixos-config" ]; then
            $DRY_RUN_CMD mkdir -p "${config.xdg.userDirs.documents}/projects/nixos-config"
          fi
          $DRY_RUN_CMD cd "${config.xdg.userDirs.documents}/projects/nixos-config"
          if [ ! -d .git ]; then
            PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD git clone git@github.com:higherorderfunctor/nixos-config.git .
          fi
          PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD git pull
          PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD git checkout ${inputs.self.sourceInfo.rev}
        '';
      };
    };
}
