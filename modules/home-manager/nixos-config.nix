{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: let
  cfg = config.nixos-config;
in {
  options.nixos-config = {
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
  config = lib.mkIf cfg.enable {
    services = {
      nixos-config = {
        Unit = {
          Description = "Clones nixos-config";
          # need networking and bind mounts to be ready
          After = [
            "network.target"
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
            nixos-config-dir = "${cfg.path}";
            nixos-config-remote = "${cfg.remote}";
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
              if [ ! -d "${nixos-config-dir}" ]; then
                # create directory if no
                mkdir -p "${nixos-config-dir}"
              fi
              # enter directory
              cd "${nixos-config-dir}"
              # check if git repo
              if [ ! -d .git ]; then
                # clone repo if no
                ${git-cmd} clone "${nixos-config-remote}" .
              else
                # fetch if yes
                ${git-cmd} fetch
              fi
              # check if dirty
              if ${git-cmd} diff-index --quiet HEAD --; then
                # update to this build if no
                ${git-cmd} checkout "${inputs.self.sourceInfo.rev}"
              fi
            '';
          }}/bin/nixos-config";
        };
      };
    };
  };
}
