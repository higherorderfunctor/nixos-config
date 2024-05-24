{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.servarr;
in {
  # machinectl list
  options.services = {
    servarr = {
      # meta service
      enable = lib.mkEnableOption "servarr";
      # vpn
      # systemctl status container@gluetun
      # sudo journalctl -M gluetun --since "1 day ago"
      # sudo nixos-container root-login gluetun
      gluetun = {
        enable = lib.mkEnableOption "gluetun" // {default = true;};
        package = lib.mkPackageOption pkgs "gluetun" {};
        settings = {
          # LOG_LEVEL=info
          logging = {
            logLevel = lib.mkOption {
              type = lib.types.enum ["debug" "info" "warn" "error"];
              default = "debug";
            };
          };

          # VPN_SERVICE_PROVIDER=pia
          # VPN_TYPE=openvpn
          # VPN_ENDPOINT_IP=
          # VPN_ENDPOINT_PORT=
          # VPN_INTERFACE=tun0
          vpn = {
            provider = lib.mkOption {
              type = lib.types.enum ["custom"];
            };
            protocol = lib.mkOption {
              type = lib.types.enum ["openvpn" "wireguard"];
            };
            interface = lib.mkOption {
              type = lib.types.str;
              default = "tun0";
            };
            portForwarding = {
              enabled = lib.mkEnableOption "portForwarding";
              provider = lib.mkOption {
                type = lib.types.str;
              };
            };
            # OPENVPN_PROTOCOL=udp
            # OPENVPN_USER=
            # OPENVPN_PASSWORD=
            # OPENVPN_USER_SECRETFILE=/run/secrets/openvpn_user
            # OPENVPN_PASSWORD_SECRETFILE=/run/secrets/openvpn_password
            # OPENVPN_VERSION=2.6
            # OPENVPN_VERBOSITY=1
            # OPENVPN_FLAGS=
            # OPENVPN_CIPHERS=
            # OPENVPN_AUTH=
            # OPENVPN_PROCESS_USER=root
            # OPENVPN_CUSTOM_CONFIG=
            # WIREGUARD_CONF_SECRETFILE=/run/secrets/wg0.conf
            # WIREGUARD_PRIVATE_KEY=
            # WIREGUARD_PRIVATE_KEY_SECRETFILE=/run/secrets/wireguard_private_key
            # WIREGUARD_PRESHARED_KEY=
            # WIREGUARD_PRESHARED_KEY_SECRETFILE=/run/secrets/wireguard_preshared_key
            # WIREGUARD_PUBLIC_KEY=
            # WIREGUARD_ALLOWED_IPS=
            # WIREGUARD_PERSISTENT_KEEPALIVE_INTERVAL=0
            # WIREGUARD_ADDRESSES=
            # WIREGUARD_ADDRESSES_SECRETFILE=/run/secrets/wireguard_addresses
            # WIREGUARD_MTU=1400
            # WIREGUARD_IMPLEMENTATION=auto
            endpoint = {
              configFile = lib.mkOption {
                type = lib.types.nullOr lib.types.path;
                default = null;
              };
            };
          };

          # HTTP_CONTROL_SERVER_LOG=on
          # HTTP_CONTROL_SERVER_ADDRESS=":8000"
          controlServer = {
            logging = lib.mkEnableOption "logging" // {default = true;};
            http = {
              listenAddress = lib.mkOption {
                type = lib.types.str;
                default = "";
              };
              port = lib.mkOption {
                type = lib.types.int;
                default = 8000;
              };
            };
          };

          # FIREWALL=on
          # FIREWALL_VPN_INPUT_PORTS=
          # FIREWALL_INPUT_PORTS=
          # FIREWALL_OUTBOUND_SUBNETS=
          # FIREWALL_DEBUG=off
          firewall = {};

          # HEALTH_SERVER_ADDRESS=127.0.0.1:9999
          # HEALTH_TARGET_ADDRESS=cloudflare.com:443
          # HEALTH_SUCCESS_WAIT_DURATION=5s
          # HEALTH_VPN_DURATION_INITIAL=6s
          # HEALTH_VPN_DURATION_ADDITION=5s
          healthCheck = {
            http = {
              listenAddress = lib.mkOption {
                type = lib.types.str;
                default = "127.0.0.1";
              };
              port = lib.mkOption {
                type = lib.types.int;
                default = 9999;
              };
            };
            target = lib.mkOption {
              type = lib.types.str;
              default = "cloudflare.com:443";
            };
            duration = {
              initial = lib.mkOption {
                type = lib.types.str;
                default = 6;
              };
              addition = lib.mkOption {
                type = lib.types.int;
                default = 5;
              };
              success = {
                wait = lib.mkOption {
                  type = lib.types.int;
                  default = 5;
                };
              };
            };
          };

          # PUBLICIP_FILE="/tmp/gluetun/ip"
          # PUBLICIP_PERIOD=12h
          # PUBLICIP_API=ipinfo
          # PUBLICIP_API_TOKEN=
          publicIp = {
            api = lib.mkOption {
              type = lib.types.enum ["ipinfo"];
              default = "ipinfo";
            };
            period = lib.mkOption {
              type = lib.types.str;
              default = "12h";
            };
            file = lib.mkOption {
              type = lib.types.path;
              default = "/run/gluetun/ip";
            };
          };

          # PPROF_ENABLED=no
          # PPROF_BLOCK_PROFILE_RATE=0
          # PPROF_MUTEX_PROFILE_RATE=0
          # PPROF_HTTP_SERVER_ADDRESS=":6060"
          pprof.enabled = lib.mkEnableOption "pprof";

          # VERSION_INFORMATION=on
          extras = {
            versionInformation = lib.mkEnableOption "versionInformation";
          };
        };
        # environmentFile = lib.mkOption {
        #   type = lib.types.nullOr lib.types.path;
        #   default = null;
        # };
        # environment = lib.mkOption rec {
        #   type = lib.types.attrsOf lib.types.str;
        #   default = {
        #     WIREGUARD_CONF_SECRETFILE = "/gluetun/wireguard/wg0.conf";
        #     HTTP_CONTROL_SERVER_LOG = "on";
        #     HTTP_CONTROL_SERVER_ADDRESS = ":8000";
        #     LOG_LEVEL = "debug";
        #   };
        #   apply = _: default // _;
        # };
        # wireguard = {
        #   config = lib.mkOption {
        #     type = lib.types.nullOr lib.types.path;
        #     default = null;
        #   };
        # };
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

  config = lib.mkIf cfg.enable {
    containers = let
      inherit (config.system) stateVersion;
      envPath = "/run/gluetun/environment";
    in {
      gluetun = lib.mkIf cfg.gluetun.enable {
        autoStart = true;
        enableTun = true;
        ephemeral = true;
        restartIfChanged = true;
        privateNetwork = true;
        hostAddress = "192.168.100.10";
        localAddress = "192.168.100.11";
        hostAddress6 = "fc00::1";
        localAddress6 = "fc00::2";
        bindMounts = lib.mkMerge [
          (lib.attrsets.optionalAttrs (! builtins.isNull cfg.gluetun.environmentFile) {
            ${envPath} = {
              hostPath = cfg.gluetun.environmentFile;
              isReadOnly = true;
            };
          })
          (lib.attrsets.optionalAttrs (! builtins.isNull cfg.gluetun.wireguard.config) {
            ${cfg.gluetun.environment.WIREGUARD_CONF_SECRETFILE} = {
              hostPath = cfg.gluetun.wireguard.config;
              isReadOnly = true;
            };
          })
        ];
        # WIREGUARD_CONF_SECRETFILE=/run/secrets/wg0.conf
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

            path = with pkgs; [
              iptables
            ];

            serviceConfig = {
              # Environment = lib.attrsets.mapAttrsToList (key: value: "${key}=${value}") cfg.gluetun.environment;
              EnvironmentFile = lib.mapNullable (_: "${envPath}") cfg.gluetun.environmentFile;
              ExecStartPre = [''${lib.getExe pkgs.bash} -c "env"''];
              ExecStart = "${lib.getExe cfg.gluetun.package}";
              Restart = "on-failure";
              RestartSec = "5s";
            };
          };

          environment.sessionVariables = cfg.gluetun.environment;

          system.stateVersion = stateVersion;

          networking = {
            firewall = {
              enable = true;
              interfaces = {
                eth0 = {
                  allowedTCPPorts = [8000 8888 8388];
                  allowedUDPPorts = [8388];
                };
              };
            };
            # use systemd-resolved inside the container
            # workaround for bug https://github.com/nixos/nixpkgs/issues/162686
            useHostResolvConf = lib.mkForce false;
          };

          services = {
            resolved.enable = true;
            timesyncd.enable = true;
          };
        };
      };
    };
  };
}
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
