{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.servarr;
in {
  # systemctl status container@servarr-vpn
  # sudo journalctl -M servarr-vpn --since "1 day ago"
  # sudo nixos-container root-login servarr-vpn
  options = {
    services.servarr.vpn = {
      enable = lib.mkEnableOption "servar-vpn" // {default = true;};
      endpoint = lib.mkOption {
        type = lib.types.str;
      };
      address = lib.mkOption {
        type = lib.types.listOf lib.types.str;
      };
      publicKey = lib.mkOption {
        type = lib.types.str;
      };
      privateKeyFile = lib.mkOption {
        type = lib.types.path;
      };
      interfaces = {
        gateway = {
          name = lib.mkOption {
            type = lib.types.str;
            default = "servarr-gw0";
          };
          address = lib.mkOption {
            type = lib.types.str;
            default = "10.100.0.0";
          };
          prefixLength = lib.mkOption {
            type = lib.types.int;
            default = 31;
          };
        };
        bridge = {
          name = lib.mkOption {
            type = lib.types.str;
            default = "servarr-br0";
          };
          address = lib.mkOption {
            type = lib.types.str;
            default = "10.100.1.0";
          };
          prefixLength = lib.mkOption {
            type = lib.types.int;
            default = 24;
          };
        };
      };
    };
  };

  config = let
    iptables = lib.getExe' pkgs.iptables "iptables";
  in
    lib.mkIf cfg.enable {
      networking = {
        bridges = {
          servarr-gw0.interfaces = [];
          servarr-br0.interfaces = [];
        };
        interfaces = {
          servarr-gw0 = {
            virtual = true;
            ipv4.addresses = [
              {
                inherit (cfg.vpn.interfaces.gateway) address prefixLength;
              }
            ];
          };
          servarr-br0 = {
            virtual = true;
          };
        };
        # nat or explicit port forwarding is needed for the VPN return traffic # TODO: port forwarding
        nat = {
          enable = lib.mkForce true;
          internalInterfaces = [cfg.vpn.interfaces.gateway.name];
        };
        firewall = {
          enable = lib.mkForce true; # needed for nat
          extraCommands = ''
            ${iptables} \
              -t mangle \
              -I PREROUTING \
              -i ${cfg.vpn.interfaces.bridge.name} \
              -s ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
              -j ACCEPT
            ${iptables} \
              -t mangle \
              -I PREROUTING \
              -i ${cfg.vpn.interfaces.bridge.name} \
              -d ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
              -j ACCEPT
          '';
          extraStopCommands = ''
            ${iptables} \
              -t mangle \
              -D PREROUTING \
              -i ${cfg.vpn.interfaces.bridge.name} \
              -s ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
              -j ACCEPT
            ${iptables} \
              -t mangle \
              -D PREROUTING \
              -i ${cfg.vpn.interfaces.bridge.name} \
              -d ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
              -j ACCEPT
          '';
        };
        # firewall.logRefusedPackets = true;
        # firewall.logRefusedUnicastsOnly = false;
      };
      containers = {
        servarr-vpn = let
          privateKeyFile = "/run/secrets/servarr/vpn/private.key";
        in
          lib.mkIf cfg.vpn.enable {
            autoStart = true;
            ephemeral = true;
            restartIfChanged = true;
            privateNetwork = true;
            extraVeths = {
              ve-vpn-eth0 = {
                hostBridge = "servarr-br0";
                localAddress = "10.100.1.2/24";
              };
              ve-vpn-eth1 = {
                hostBridge = "servarr-gw0";
                localAddress = "10.100.0.1/31";
              };
            };
            bindMounts = lib.mkMerge [
              {
                ${privateKeyFile} = {
                  hostPath = cfg.vpn.privateKeyFile;
                  isReadOnly = true;
                };
              }
            ];
            config = {
              pkgs,
              lib,
              ...
            }: let
              wg = lib.getExe pkgs.wireguard-tools;
              wg-interface = "wg0";
            in {
              system.stateVersion = config.system.stateVersion;

              environment.systemPackages = [pkgs.tcpdump];

              # boot.kernel.sysctl."net.ipv4.ip_forward" = 1;
              networking = {
                firewall = {
                  enable = false; # FIXME: true;
                };
                # nat = {
                #   enable = true;
                #   externalInterface = "${wg-interface}";
                #   internalInterfaces = ["ve-vpn-eth0"];
                # };
                # interfaces.ve-vpn-eth0.ipv4.routes = [
                #   {
                #     address = "10.100.1.0";
                #     prefixLength = 24;
                #     via = "10.100.1.1";
                #   }
                # ];
                interfaces.ve-vpn-eth1.ipv4.routes = [
                  {
                    address = "10.100.0.0";
                    prefixLength = 31;
                    via = "10.100.0.0";
                  }
                  {
                    address = builtins.elemAt (lib.strings.split ":" cfg.vpn.endpoint) 0;
                    prefixLength = 32;
                    via = "10.100.0.0";
                  }
                ];
                wireguard.interfaces = {
                  "${wg-interface}" = {
                    ips = cfg.vpn.address;
                    listenPort = 51820;
                    inherit privateKeyFile;
                    peers = [
                      {
                        inherit (cfg.vpn) endpoint publicKey;
                        allowedIPs = ["0.0.0.0/1" "128.0.0.0/1"];
                        persistentKeepalive = 25;
                      }
                    ];
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
        servarr-test = lib.mkIf cfg.vpn.enable {
          autoStart = true;
          ephemeral = true;
          restartIfChanged = true;
          privateNetwork = true;
          extraVeths = {
            ve-test-eth0 = {
              hostBridge = "servarr-br0";
              localAddress = "10.100.1.3/24";
            };
          };
          config = {
            pkgs,
            lib,
            ...
          }: {
            system.stateVersion = config.system.stateVersion;

            environment.systemPackages = [pkgs.tcpdump];

            networking = {
              firewall.enable = false;
              # defaultGateway = {
              #   interface = "ve-test-eth0";
              #   address = "10.100.1.1";
              # };

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
