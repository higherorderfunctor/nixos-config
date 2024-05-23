{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.servarr;
in {
  options.services = {
    servarr = {
      # meta service
      enable = lib.mkEnableOption "servarr";
      # vpn
      gluetun = {
        enable = lib.mkEnableOption "gluetun" // {default = true;};
        package = lib.mkPackageOption pkgs "gluetun" {};
      };
      # movies
      radarr = {
        enable = lib.mkEnableOption "radarr" // {default = true;};
        package = lib.mkPackageOption // {default = pkgs.radarr;};
      };
      # tv shows
      sonarr = {
        enable = lib.mkEnableOption "sonarr" // {default = true;};
        package = lib.mkPackageOption // {default = pkgs.sonarr;};
      };
      # indexer
      prowlarr = {
        enable = lib.mkEnableOption "prowlarr" // {default = true;};
        package = lib.mkPackageOption // {default = pkgs.prowlarr;};
      };
    };
  };

  config.containers = lib.mkIf cfg.enable {
    gluetun = lib.mkIf cfg.gluetun.enable {
      autoStart = true;
      privateNetwork = true;
      hostAddress = "192.168.100.10";
      localAddress = "192.168.100.11";
      hostAddress6 = "fc00::1";
      localAddress6 = "fc00::2";
      config = {
        config,
        pkgs,
        lib,
        ...
      }: {
        systemd.services.gluetun = {
          description = "gluetun";
          after = ["network.target"];
          wantedBy = ["multi-user.target"];

          serviceConfig = {
            ExecStart = "${lib.getExe pkgs.gluetun}";
            Restart = "on-failure";
            RestartSec = "10s";
          };
        };

        system.stateVersion = config.system.stateVersion;

        networking = {
          firewall = {
            enable = true;
            allowedTCPPorts = [80];
          };
          # use systemd-resolved inside the container
          # workaround for bug https://github.com/nixos/nixpkgs/issues/162686
          useHostResolvConf = lib.mkForce false;
        };

        services.resolved.enable = true;
      };
    };
  };
  #config.systemd.user.services = lib.mkIf cfg.enable {
  #  nixos-config = {
  #    Unit = {
  #      Description = "Clones nixos-config";
  #      # need networking and bind mounts to be ready
  #      Wants = [
  #        "network-online.target"
  #      ];
  #      After = [
  #        "network.target"
  #        "network-online.target"
  #        "paths.target"
  #      ];
  #    };
  #    Install = {
  #      WantedBy = ["default.target"];
  #    };
  #    Service = {
  #      Type = "oneshot";
  #      StandardOutput = "journal+console";
  #      StandardError = "journal+console";
  #      ExecStart = let
  #        git-cmd = lib.concatMapStrings (s: s + " ") [
  #          "GIT_SSH_COMMAND=\"ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no\""
  #          "git"
  #        ];
  #      in "${pkgs.writeShellApplication {
  #        name = "nixos-config";
  #        runtimeInputs = with pkgs; [
  #          coreutils-full
  #          git
  #          gnugrep
  #          openssh
  #        ];
  #        text = ''
  #          set -euETo pipefail
  #          shopt -s inherit_errexit

  #          # check if directory exists
  #          if [ ! -d "${cfg.path}" ]; then
  #            # create directory if no
  #            mkdir -p "${cfg.path}"
  #          fi
  #          # enter directory
  #          cd "${cfg.path}"
  #          # check if git repo
  #          if [ ! -d .git ]; then
  #            # clone repo if no
  #            ${git-cmd} clone "${cfg.remote}" .
  #          else
  #            # fetch if yes
  #            ${git-cmd} fetch
  #          fi
  #        '';
  #      }}/bin/nixos-config";
  #    };
  #  };
  #};
}
