{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.servarr;
  # TODO: real subnet checking
  offsetIpv4Address = address: offset: let
    octets = lib.splitString "." address;
    networkBits = lib.lists.sublist 0 3 octets;
    hostBits = builtins.toString (lib.strings.toInt (lib.lists.last octets) + offset);
  in
    lib.strings.concatStringsSep "." (networkBits ++ [hostBits]);
in {
  # TODO: allow local network to access services
  #
  # systemctl status container@servarr-vpn
  # sudo journalctl -M servarr-vpn --since "1 day ago"
  # sudo nixos-container root-login servarr-vpn
  #
  # sudo tcpdump -tttt -n -q -c 100
  #
  # echo "FILTER"; sudo iptables -L -v -n --line-numbers -t filter     | grep -P "Chain|drop"
  # echo "NAT"; sudo iptables -L -v -n --line-numbers -t nat           | grep -P "Chain|drop"
  # echo "MANGLE"; sudo iptables -L -v -n --line-numbers -t mangle     | grep -P "Chain|drop"
  # echo "RAW"; sudo iptables -L -v -n --line-numbers -t raw           | grep -P "Chain|drop"
  # echo "SECURITY"; sudo iptables -L -v -n --line-numbers -t security | grep -P "Chain|drop"
  options = {
    services.servarr.vpn = {
      enable = lib.mkEnableOption "servar-vpn" // {default = true;};
      endpoint = {
        address = lib.mkOption {
          type = lib.types.str;
        };
        port = lib.mkOption {
          type = lib.types.int;
          default = 51820;
        };
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
          hostAddress = lib.mkOption {
            type = lib.types.str;
            default = "10.100.0.0";
          };
          localAddress = lib.mkOption {
            type = lib.types.str;
            default = "10.100.0.1";
          };
          # address = lib.mkOption {
          #   type = lib.types.str;
          #   default = "10.100.0.0";
          # };
          # prefixLength = lib.mkOption {
          #   type = lib.types.int;
          #   default = 31; # FIXME: min 31
          # };
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
            default = 24; # FIXME: min based on num services enabled
          };
        };
      };
    };
  };

  config = let
    iptables = lib.getExe' pkgs.iptables "iptables";
  in
    lib.mkIf cfg.enable {
      # HOST CONFIGURATION
      networking = {
        bridges = {
          # "${cfg.vpn.interfaces.gateway.name}".interfaces = [];
          "${cfg.vpn.interfaces.bridge.name}".interfaces = [];
        };
        interfaces = {
          # "${cfg.vpn.interfaces.gateway.name}" = {
          #   virtual = true;
          #   ipv4.addresses = [
          #     {
          #       inherit (cfg.vpn.interfaces.gateway) address prefixLength;
          #     }
          #   ];
          # };
          "${cfg.vpn.interfaces.bridge.name}" = {
            virtual = true;
          };
        };
        # forward return traffic from wireguard peer to vpn container's wireguard client
        nat = {
          enable = lib.mkForce true;
          internalInterfaces = ["ve-vpn-eth1"];
        };
        firewall = {
          # needed for nat
          # enable = lib.mkForce true;
          # FIXME: also only allow traffic from wireguard endpoint host not just port
          # interfaces."${cfg.vpn.interfaces.gateway.name}".allowedUDPPorts = [cfg.vpn.endpoint.port];
          # allows traffic over the VPN bridge without settings an IP on the host side of the bridge
          # extraCommands = ''
          #   ${iptables} -I nixos-fw-log-refuse 2 -m limit --limit 10/min -j LOG --log-prefix "dropped packet: " --log-level 6
          # '';
          #   ${iptables} -I nixos-fw -o ve-vpn-eth1 -j nixos-fw-accept
          #   ${iptables} -I nixos-fw -i ve-vpn-eth1 -j nixos-fw-accept
          extraCommands = ''
            ${iptables} -t mangle -I nixos-fw-rpfilter -i ${cfg.vpn.interfaces.bridge.name} -m rpfilter --validmark --loose -j RETURN
          '';
          # ${iptables} \
          #   -t mangle \
          #   -I PREROUTING \
          #   -i ${cfg.vpn.interfaces.bridge.name} \
          #   -s ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
          #   -j ACCEPT
          # ${iptables} \
          #   -t mangle \
          #   -I PREROUTING \
          #   -i ${cfg.vpn.interfaces.bridge.name} \
          #   -d ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
          #   -j ACCEPT
          extraStopCommands = ''
            ${iptables} -t mangle -D nixos-fw-rpfilter -i ${cfg.vpn.interfaces.bridge.name} -m rpfilter --validmark --loose -j RETURN
          '';
          #   ${iptables} -D nixos-fw -o ve-vpn-eth1 -j nixos-fw-accept
          #   ${iptables} -D nixos-fw -i ve-vpn-eth1 -j nixos-fw-accept
          #   ${iptables} \
          #     -t mangle \
          #     -D PREROUTING \
          #     -i ${cfg.vpn.interfaces.bridge.name} \
          #     -s ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
          #     -j ACCEPT
          #   ${iptables} \
          #     -t mangle \
          #     -D PREROUTING \
          #     -i ${cfg.vpn.interfaces.bridge.name} \
          #     -d ${cfg.vpn.interfaces.bridge.address}/${builtins.toString cfg.vpn.interfaces.bridge.prefixLength} \
          #     -j ACCEPT
        };
      };
      containers = {
        # VPN CONTAINER
        servarr-vpn = let
          privateKeyFile = "/run/secrets/servarr/vpn/private.key";
        in
          lib.mkIf cfg.vpn.enable {
            autoStart = true;
            ephemeral = true;
            restartIfChanged = true;
            privateNetwork = true;
            extraVeths = {
              # wireguard bridge for all the containers that this container will route over wireguard
              ve-vpn-eth0 = {
                hostBridge = cfg.vpn.interfaces.bridge.name;
                localAddress = lib.concatStringsSep "/" [
                  (offsetIpv4Address cfg.vpn.interfaces.bridge.address 1)
                  (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
                ]; # "10.100.1.1/24";
              };
              # internet gateway interface to route wireguard traffic
              ve-vpn-eth1 = {
                # hostBridge = cfg.vpn.interfaces.gateway.name;
                inherit (cfg.vpn.interfaces.gateway) hostAddress localAddress;
                # localAddress = lib.concatStringsSep "/" [
                #   (offsetIpv4Address cfg.vpn.interfaces.gateway.address 0)
                #   (builtins.toString cfg.vpn.interfaces.gateway.prefixLength)
                # ]; # "10.100.0.1/31";
              };
            };
            bindMounts = lib.mkMerge [
              # mount the private key file from the host
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

              environment.systemPackages = (with pkgs.bind; [dnsutils host]) ++ [pkgs.tcpdump];

              networking = {
                firewall = {
                  enable = true;
                };
                nat = {
                  enable = true;
                  externalInterface = "${wg-interface}";
                  internalInterfaces = ["ve-vpn-eth0"];
                };
                # TODO: FIXME: dig @8.8.8.8 @8.8.4.4  TXT o-o.myaddr.l.google.com +short
                interfaces = {
                  # ve-vpn-eth0.ipv4.routes = [
                  #   {
                  #     address = "10.100.1.0";
                  #     prefixLength = 24;
                  #     via = "10.100.1.1";
                  #   }
                  # ];
                  ve-vpn-eth1.ipv4.routes = [
                    # # prevents traffic to the host from being broadcast traffic
                    # # which is blocked by default on the nix firewall
                    # {
                    #   inherit (cfg.vpn.interfaces.gateway) address;
                    #   prefixLength = 32;
                    #   via = cfg.vpn.interfaces.gateway.address;
                    # }
                    # routes wireguard peer traffic out the gateway
                    {
                      inherit (cfg.vpn.endpoint) address;
                      prefixLength = 32;
                      via = cfg.vpn.interfaces.gateway.hostAddress;
                    }
                  ];
                };
                # wireguard configuration
                wireguard.interfaces = {
                  "${wg-interface}" = {
                    ips = cfg.vpn.address;
                    listenPort = cfg.vpn.endpoint.port;
                    inherit privateKeyFile;
                    peers = [
                      {
                        endpoint = "${cfg.vpn.endpoint.address}:${builtins.toString cfg.vpn.endpoint.port}";
                        inherit (cfg.vpn) publicKey;
                        allowedIPs = ["0.0.0.0/1" "128.0.0.0/1"]; # force default route traffic through VPN
                        persistentKeepalive = 25;
                      }
                    ];
                  };
                };
              };
            };
          };

        # VPN TEST CONTAINER
        servarr-test = lib.mkIf cfg.vpn.enable {
          autoStart = true;
          ephemeral = true;
          restartIfChanged = true;
          privateNetwork = true;
          extraVeths = {
            # wireguard bridge for all the containers to forward traffic over the vpn
            ve-test-eth0 = {
              hostBridge = cfg.vpn.interfaces.bridge.name;
              localAddress = lib.concatStringsSep "/" [
                (offsetIpv4Address cfg.vpn.interfaces.bridge.address 2)
                (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
              ]; # "10.100.1.1/24";
            };
          };
          config = {
            pkgs,
            lib,
            ...
          }: {
            system.stateVersion = config.system.stateVersion;

            environment.systemPackages = (with pkgs.bind; [dnsutils host]) ++ [pkgs.tcpdump];

            networking = {
              firewall.enable = false;
              defaultGateway = {
                interface = "ve-test-eth0";
                address = offsetIpv4Address cfg.vpn.interfaces.bridge.address 1;
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
