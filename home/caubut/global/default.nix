{
  config,
  inputs,
  lib,
  pkgs,
  specialArgs,
  ...
}: let
  # inherit (specialArgs) hostname;
  username = "caubut"; # TODO: get from system
in {
  imports = [
    # inputs.impermanence.nixosModules.home-manager.impermanence
    # inputs.sops-nix.homeManagerModules.sops
    ../features/cli
    ../features/desktop
    ../features/colors/catppuccin-mocha.nix
  ];

  nixpkgs = {
    #   overlays = [
    #     inputs.neovim-nightly-overlay.overlay
    #   ];
    config = {
      allowUnfree = true;
    };
  };

  programs = {
    home-manager.enable = true;
    oh-my-posh.enable = true;
    # starship.enable = true;
    # ssh.enable = true;
  };

  xdg = {
    enable = true;
    userDirs = {
      enable = true;
      createDirectories = true;
    };

    mime.enable = true;
  };

  # # TODO: # secrets
  # # sops = {
  # #   defaultSopsFile = ../secrets/secrets.yaml;
  # #   secrets = {
  # #     "${config.home.username}-secret-key" = {
  # #       path = "${config.home.homeDirectory}/.ssh/id_ed25519";
  # #       mode = "600";
  # #     };
  # #   };
  # # };

  systemd.user = {
    # switches services on rebuilds
    startServices = "sd-switch";
    #   #   # permission fixes
    #   #   tmpfiles.rules = [
    #   #     "z /home/${username}/.ssh 0700 ${username} ${username} - -"
    #   #     "z /persist/home/${username}/.ssh 0700 ${username} ${username} - -"
    #   #     "z /home/${username}/.local 0700 ${username} ${username} - -"
    #   #     "z /persist/home/${username}/.local 0700 ${username} ${username} - -"
    #   #     "z /home/${username}/.local/share 0700 ${username} ${username} - -"
    #   #     "z /persist/home/${username}/.local/share 0700 ${username} ${username} - -"
    #   #   ];
    #   #   services = {
    #   #     nixos-config = {
    #   #       Unit = {
    #   #         Description = "Clones nixos-config";
    #   #         # need networking and bind mounts to be ready
    #   #         After = ["network.target" "paths.target"];
    #   #       };
    #   #       Install = {
    #   #         WantedBy = ["default.target"];
    #   #       };
    #   #       Service = {
    #   #         Type = "oneshot";
    #   #         StandardOutput = "journal+console";
    #   #         StandardError = "journal+console";
    #   #         ExecStart = let
    #   #           nixos-config-dir = "${config.xdg.userDirs.documents}/projects/nixos-config";
    #   #           nixos-config-repo = "git@github.com:higherorderfunctor/nixos-config.git";
    #   #           git-cmd = lib.concatMapStrings (s: s + " ") [
    #   #             "GIT_SSH_COMMAND=\"ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no\""
    #   #             "git"
    #   #           ];
    #   #         in "${pkgs.writeShellApplication {
    #   #           name = "nixos-config";
    #   #           runtimeInputs = with pkgs; [
    #   #             coreutils-full
    #   #             git
    #   #             gnugrep
    #   #             openssh
    #   #           ];
    #   #           text = ''
    #   #             set -euETo pipefail
    #   #             shopt -s inherit_errexit

    #   #             # check if directory exists
    #   #             if [ ! -d "${nixos-config-dir}" ]; then
    #   #               # create directory if no
    #   #               mkdir -p "${nixos-config-dir}"
    #   #             fi
    #   #             # enter directory
    #   #             cd "${nixos-config-dir}"
    #   #             # check if git repo
    #   #             if [ ! -d .git ]; then
    #   #               # clone repo if no
    #   #               ${git-cmd} clone "${nixos-config-repo}" .
    #   #             else
    #   #               # fetch if yes
    #   #               ${git-cmd} fetch
    #   #             fi
    #   #             # reset frequently updated lock file
    #   #             if ${git-cmd} status --porcelain | grep -q '^ M home/caubut/features/neovim/nvim-config/lazy-lock.json'; then
    #   #             ${git-cmd} checkout HEAD -- home/caubut/features/neovim/nvim-config/lazy-lock.json
    #   #             fi
    #   #             # check if dirty
    #   #             if ${git-cmd} diff-index --quiet HEAD --; then
    #   #               # update to this build if no
    #   #               ${git-cmd} checkout "${inputs.self.sourceInfo.rev}"
    #   #             else
    #   #               # fail if yet
    #   #               echo "Failed to setup nixos-config" >&2
    #   #               >&2 echo "Failed to setup nixos-config"
    #   #               # TODO: Logger
    #   #               exit 1
    #   #             fi
    #   #           '';
    #   #         }}/bin/nixos-config";
    #   #       };
    #   #     };
    #   #   };
  };

  # TODO: non-nixos only
  targets.genericLinux.enable = true;

  home = {
    # pin system and home-manager state versions
    inherit (import ../../../hosts/common/global/state-version.nix) stateVersion;
    inherit username;
    homeDirectory = "/home/${username}";
    # sessionVariables = {
    #   # XDG_DATA_DIRS = "${config.home.profileDirectory}/share:$XDG_DATA_DIRS";
    #   # XDG_DATA_DIRS =
    #   #   lib.mkIf (lib.hasAttr "XDG_DATA_DIRS" config.home.sessionVariables)
    #   #   (lib.mkBefore "${config.home.profileDirectory}/share:${builtins.getEnv "XDG_DATA_DIRS"}")
    #   #   "${config.home.profileDirectory}/share";
    #   #     NIXOS_HOST = hostname;
    # };
    #   persistence = {
    #     "/persist/home/${username}" = {
    #       directories = [
    #         "Documents"
    #         "Downloads"
    #         "Pictures"
    #         "Videos"
    #       ];
    #       files = [
    #         ".ssh/known_hosts"
    #       ];
    #       allowOther = true;
    #     };
    #   };
    #   file = {
    #     ".ssh/id_ed25519".source = config.lib.file.mkOutOfStoreSymlink "/run/secrets/${username}-secret-key";
    #     ".ssh/id_ed25519.pub".source = ../secrets/id_ed25519.pub;
    #   };
  };
}
