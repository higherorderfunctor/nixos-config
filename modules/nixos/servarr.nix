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
            # VPN_PORT_FORWARDING=
            # VPN_PORT_FORWARDING_PROVIDER=
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
          firewall = {
            enable = lib.mkEnableOption "firewall" // {default = true;};
          };

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
                type = lib.types.int;
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
          pprof = {
            enabled = lib.mkEnableOption "pprof";
            blockProfileRate = lib.mkOption {
              type = lib.types.int;
              default = 0;
            };
            mutexProfileRate = lib.mkOption {
              type = lib.types.int;
              default = 0;
            };
            http = {
              listenAddress = lib.mkOption {
                type = lib.types.str;
                default = "";
              };
              port = lib.mkOption {
                type = lib.types.int;
                default = 6060;
              };
            };
          };

          # VERSION_INFORMATION=on
          extras = {
            versionInformation = lib.mkEnableOption "versionInformation";
          };
        };
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
      env = {
        LOG_LEVEL = cfg.gluetun.settings.logging.logLevel;

        VPN_SERVICE_PROVIDER = cfg.gluetun.settings.vpn.provider;
        VPN_TYPE = cfg.gluetun.settings.vpn.protocol;
        VPN_INTERFACE = cfg.gluetun.settings.vpn.interface;
        VPN_PORT_FORWARDING =
          if cfg.gluetun.settings.vpn.portForwarding.enabled
          then "on"
          else "off";
        VPN_PORT_FORWARDING_PROVIDER = cfg.gluetun.settings.vpn.portForwarding.provider;

        HTTP_CONTROL_SERVER_LOG =
          if cfg.gluetun.settings.controlServer.logging
          then "on"
          else "off";
        HTTP_CONTROL_SERVER_ADDRESS = lib.concatStringsSep ":" [
          "${cfg.gluetun.settings.controlServer.http.listenAddress}"
          "${builtins.toString cfg.gluetun.settings.controlServer.http.port}"
        ];

        FIREWALL =
          if cfg.gluetun.settings.firewall.enable
          then "on"
          else "off";

        HEALTH_SERVER_ADDRESS = lib.concatStringsSep ":" [
          "${cfg.gluetun.settings.healthCheck.http.listenAddress}"
          "${builtins.toString cfg.gluetun.settings.healthCheck.http.port}"
        ];
        HEALTH_TARGET_ADDRESS = cfg.gluetun.settings.healthCheck.target;
        HEALTH_SUCCESS_WAIT_DURATION = "${builtins.toString cfg.gluetun.settings.healthCheck.duration.success.wait}s";
        HEALTH_VPN_DURATION_INITIAL = "${builtins.toString cfg.gluetun.settings.healthCheck.duration.initial}s";
        HEALTH_VPN_DURATION_ADDITION = "${builtins.toString cfg.gluetun.settings.healthCheck.duration.addition}s";

        PUBLICIP_FILE = "${cfg.gluetun.settings.publicIp.file}";
        PUBLICIP_PERIOD = "${cfg.gluetun.settings.publicIp.period}";
        PUBLICIP_API = "${cfg.gluetun.settings.publicIp.api}";

        PPROF_ENABLED =
          if cfg.gluetun.settings.pprof.enabled
          then "on"
          else "off";
        PPROF_BLOCK_PROFILE_RATE = "${builtins.toString cfg.gluetun.settings.pprof.blockProfileRate}";
        PPROF_MUTEX_PROFILE_RATE = "${builtins.toString cfg.gluetun.settings.pprof.mutexProfileRate}";
        PPROF_HTTP_SERVER_ADDRESS = lib.concatStringsSep ":" [
          "${cfg.gluetun.settings.pprof.http.listenAddress}"
          "${builtins.toString cfg.gluetun.settings.pprof.http.port}"
        ];

        VERSION_INFORMATION =
          if cfg.gluetun.settings.extras.versionInformation
          then "on"
          else "off";
      };
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
          (lib.attrsets.optionalAttrs (! builtins.isNull cfg.gluetun.settings.vpn.endpoint.configFile) {
            "/gluetun/wireguard/wg0.conf" = {
              hostPath = cfg.gluetun.settings.vpn.endpoint.configFile;
              isReadOnly = true;
            };
          })
        ];
        config = {
          pkgs,
          lib,
          ...
        }: {
          systemd.services.gluetun = {
            description = "gluetun";
            after = ["network.target"];
            wantedBy = ["multi-user.target"];

            path =
              (with pkgs; [
                iptables
                unbound-full
              ])
              ++ [
                (pkgs.stdenvNoCC.mkDerivation {
                  inherit (pkgs.openvpn) pname version;
                  nativeBuildInputs = with pkgs; [makeWrapper];
                  buildInputs = with pkgs; [openvpn];
                  phases = ["installPhase"];
                  installPhase = ''
                    mkdir -p $out/bin
                    makeWrapper ${lib.getExe pkgs.openvpn} $out/bin/openvpn2.5
                    makeWrapper ${lib.getExe pkgs.openvpn} $out/bin/openvpn2.6
                  '';
                })
              ];

            serviceConfig = {
              EnvironmentFile =
                builtins.toFile "environment"
                (builtins.concatStringsSep "\n"
                  (lib.mapAttrsToList (name: value: "${name}=${value}") env));
              # ExecStartPre = ''
              #   ${pkgs.coreutils}/bin/mkdir -p /usr/sbin
              #   ln -sfn ${lib.getExe' pkgs.unbound-full "unbound"} /usr/sbin/unbound
              # '';
              ExecStart = "${lib.getExe cfg.gluetun.package}";
              Restart = "on-failure";
              RestartSec = "5s";
            };
          };

          system.stateVersion = stateVersion;

          environment = {
            # systemPackages = [
            #   (pkgs.unbound-full.overrideAttrs (attrs: {
            #     nativeBuildInputs = attrs.nativeBuildInputs ++ (with pkgs; [makeWrapper]);
            #     postFixup = ''
            #       mkdir -p $out/usr/sbin
            #       makeWrapper ${lib.getExe' pkgs.unbound-full "unbound"} $out/usr/sbin/unbound
            #     '';
            #   }))
            # ];
            etc = {
              alpine-release.source = config.environment.etc.os-release.source;
            };
          };

          networking = {
            firewall = {
              enable = true;
              interfaces = {
                eth0 = {
                  allowedTCPPorts = [8000 8888 8388]; # TODO: dynamic
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
