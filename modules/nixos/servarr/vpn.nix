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
    wan-interface = "ve-vpn-eth1";
    br-interface = cfg.vpn.interfaces.bridge.name;
  in
    lib.mkIf cfg.enable {
      # HOST CONFIGURATION
      networking = {
        bridges = {
          # creates a bridge connecting all the containers
          "${br-interface}".interfaces = [];
        };
        interfaces = {
          # sets the host interface to be virtual without an IP address
          "${br-interface}" = {
            virtual = true;
          };
        };
        # forwards return traffic to the wireguard container's wan interface
        nat = {
          enable = lib.mkForce true;
          internalInterfaces = [wan-interface];
        };
        firewall = {
          enable = lib.mkForce true;
          # limits traffic to the wireguard container's wan interface
          interfaces.${wan-interface}.allowedUDPPorts = [
            # allows return traffic from the wireguard peer
            cfg.vpn.endpoint.port
          ];
          # allows traffic forwarding on the host bridge without an IP address on the host interface
          extraCommands = ''
            ${iptables} -t mangle -I nixos-fw-rpfilter -i ${br-interface} -m rpfilter --validmark --loose -j RETURN
          '';
          # cleans up rule(s) and prevents failures when recovering from a broken state
          extraStopCommands = ''
            ${iptables} -t mangle -D nixos-fw-rpfilter -i ${br-interface} -m rpfilter --validmark --loose -j RETURN || true
          '';
        };
      };
      containers = {
        # VPN CONTAINER
        servarr-vpn = let
          privateKeyFile = "/run/secrets/servarr/vpn/private.key";
          lan-interface = "ve-vpn-eth0";
        in
          lib.mkIf cfg.vpn.enable {
            autoStart = true;
            ephemeral = true;
            restartIfChanged = true;
            privateNetwork = true;
            extraVeths = {
              # connects to the bridge connecting all the containers
              ${lan-interface} = {
                hostBridge = br-interface;
                localAddress = lib.concatStringsSep "/" [
                  (offsetIpv4Address cfg.vpn.interfaces.bridge.address 1)
                  (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
                ];
              };
              # creates an internet gateway interface to route wireguard traffic
              ${wan-interface} = {
                inherit (cfg.vpn.interfaces.gateway) hostAddress localAddress;
              };
            };
            bindMounts = lib.mkMerge [
              # mounts the private key file from the host
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

              environment.systemPackages =
                (with pkgs.bind; [dnsutils host])
                ++ (with pkgs; [knot-dns tcpdump]);

              networking = {
                firewall = {
                  # TODO: block dns
                  enable = true;
                  # limits traffic to the wireguard container's wan interface
                  interfaces.${wan-interface}.allowedUDPPorts = [
                    # allows return traffic from the wireguard peer
                    cfg.vpn.endpoint.port
                  ];
                  # blocks cleartext DNS from going over wireguard
                  extraCommands = ''
                    ${iptables} -A OUTPUT -o ${wg-interface} -p udp --dport 53 -j DROP
                    ${iptables} -A OUTPUT -o ${wg-interface} -p tcp --dport 53 -j DROP
                  '';
                  # cleans up rule(s) and prevents failures when recovering from a broken state
                  extraStopCommands = ''
                    ${iptables} -D OUTPUT -o ${wg-interface} -p udp --dport 53 -j DROP || true
                    ${iptables} -D OUTPUT -o ${wg-interface} -p tcp --dport 53 -j DROP || true
                  '';
                };
                # forwards and nats all traffic from the bridge over the wireguard interface
                nat = {
                  enable = true;
                  externalInterface = wg-interface;
                  internalInterfaces = [lan-interface];
                };
                # TODO: FIXME: dig @8.8.8.8 @8.8.4.4  TXT o-o.myaddr.l.google.com +short
                # kdig +tls @8.8.8.8 @8.8.4.4 TXT o-o.myaddr.l.google.com +short
                interfaces = {
                  ${wan-interface}.ipv4.routes = [
                    # adds a more specific route for wireguard peer traffic to go out the wan interface
                    {
                      inherit (cfg.vpn.endpoint) address;
                      prefixLength = 32;
                      via = cfg.vpn.interfaces.gateway.hostAddress;
                    }
                  ];
                };
                # configures wireguard
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

              systemd = {
                # watchdog service that checks for traffic across the wireguard
                # interface and restarts wireguard on failure
                timers."watchdog@wireguard-${wg-interface}" = {
                  partOf = ["wireguard-${wg-interface}.target"];
                  wantedBy = ["timers.target" "wireguard-${wg-interface}.target"];
                  timerConfig = {
                    OnActiveSec = "1m";
                    OnUnitActiveSec = "1m";
                    Unit = "watchdog@wireguard-${wg-interface}.service";
                  };
                };
                services."watchdog@wireguard-${wg-interface}" = {
                  # systemctl list-dependencies wireguard-wg0.target
                  # systemctl list-timers
                  # systemctl status watchdog@wireguard-wg0.timer
                  # journalctl -f
                  # journalctl -u watchdog@wireguard-wg0.service
                  partOf = ["wireguard-${wg-interface}.target"];
                  path = with pkgs; [knot-dns systemd];
                  script = let
                    prefix =
                      lib.concatStringsSep "." (lib.sublist 0 3
                        (lib.splitString "." cfg.vpn.endpoint.address));
                  in ''
                    set -eu
                    ${lib.getExe' pkgs.knot-dns "kdig"} +tls @208.67.222.222 myip.opendns.com A +short | \
                      grep -F "${prefix}"
                  '';
                  serviceConfig = {
                    Type = "oneshot";
                    User = "root";
                    ExecStopPost = "${pkgs.writeShellScript "restart-wireguard-${wg-interface}.service" ''
                      if [ "$EXIT_CODE" != "exited" ] || [ "$EXIT_STATUS" != "0" ]; then
                        echo "$EXIT_CODE" "$EXIT_STATUS"
                        ${lib.getExe' pkgs.systemd "systemctl"} restart "wireguard-${wg-interface}.service"
                      fi
                    ''}";
                  };
                };
              };

              services = {
                unbound = {
                  # kdig +tls @127.0.0.1 nixos.org
                  enable = true;
                  settings = {
                    server = {
                      interface = ["127.0.0.1" lan-interface];
                      access-control = let
                        bridge-address = lib.concatStringsSep "/" [
                          cfg.vpn.interfaces.bridge.address
                          (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
                        ];
                      in [
                        "127.0.0.0/8 allow"
                        "${bridge-address} allow"
                      ];
                    };
                    forward-zone = {
                      name = ".";
                      forward-tls-upstream = "yes";
                      forward-addr = [
                        "9.9.9.9@853#dns.quad9.net"
                        "149.112.112.112@853#dns.quad9.net"
                      ];
                    };
                  };
                };
              };
            };
          };

        # VPN TEST CONTAINER
        servarr-test = let
          lan-interface = "ve-test-eth0";
        in
          lib.mkIf cfg.vpn.enable {
            autoStart = true;
            ephemeral = true;
            restartIfChanged = true;
            privateNetwork = true;
            extraVeths = {
              # connects to the bridge connecting all the containers
              ${lan-interface} = {
                hostBridge = br-interface;
                localAddress = lib.concatStringsSep "/" [
                  (offsetIpv4Address cfg.vpn.interfaces.bridge.address 2)
                  (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
                ];
              };
            };
            config = {
              pkgs,
              lib,
              ...
            }: {
              system.stateVersion = config.system.stateVersion;

              environment.systemPackages =
                (with pkgs.bind; [dnsutils host])
                ++ (with pkgs; [knot-dns tcpdump]);

              networking = {
                firewall.enable = false;
                defaultGateway = {
                  interface = lan-interface;
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
