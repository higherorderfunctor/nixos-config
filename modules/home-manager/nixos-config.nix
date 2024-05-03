{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.nixos-config;
in {
  options.services.nixos-config = {
    enable = lib.mkEnableOption "nixos-config";
    path = lib.mkOption {
      type = lib.types.str;
      description = "Path to store a nixos-config";
    };
    remote = lib.mkOption {
      type = lib.types.str;
      description = "Remote repository to clone from";
    };
  };
  config.systemd.user.services = lib.mkIf cfg.enable {
    nixos-config = {
      Unit = {
        Description = "Clones nixos-config";
        # need networking and bind mounts to be ready
        Needs = [
          "network-online.target"
        ];
        After = [
          "network.target"
          "network-online.target"
          "paths.target"
        ];
      };
      Install = {
        WantedBy = ["default.target"];
      };
      Service = {
        Type = "oneshot";
        StandardOutput = "journal+console";
        StandardError = "journal+console";
        ExecStart = let
          git-cmd = lib.concatMapStrings (s: s + " ") [
            "GIT_SSH_COMMAND=\"ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no\""
            "git"
          ];
        in "${pkgs.writeShellApplication {
          name = "nixos-config";
          runtimeInputs = with pkgs; [
            coreutils-full
            git
            gnugrep
            openssh
          ];
          text = ''
            set -euETo pipefail
            shopt -s inherit_errexit

            # check if directory exists
            if [ ! -d "${cfg.path}" ]; then
              # create directory if no
              mkdir -p "${cfg.path}"
            fi
            # enter directory
            cd "${cfg.path}"
            # check if git repo
            if [ ! -d .git ]; then
              # clone repo if no
              ${git-cmd} clone "${cfg.remote}" .
            else
              # fetch if yes
              ${git-cmd} fetch
            fi
          '';
        }}/bin/nixos-config";
      };
    };
  };
}
