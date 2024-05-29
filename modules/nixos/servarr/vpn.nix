{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg' = config;
  cfg = config.services.servarr;
  inherit (config.system) stateVersion;
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
  # journalctl -u container@servarr-vpn
  # sudo journalctl -M servarr-vpn --since "1 day ago"
  # sudo nixos-container root-login servarr-vpn
  #
  # sudo tcpdump -tttt -n -q -c 100
  #
  # echo "FILTER"; sudo iptables -L -v -n --line-numbers -t filter     | grep -P "Chain|DROP"
  # echo "NAT"; sudo iptables -L -v -n --line-numbers -t nat           | grep -P "Chain|DROP"
  # echo "MANGLE"; sudo iptables -L -v -n --line-numbers -t mangle     | grep -P "Chain|DROP"
  # echo "RAW"; sudo iptables -L -v -n --line-numbers -t raw           | grep -P "Chain|DROP"
  # echo "SECURITY"; sudo iptables -L -v -n --line-numbers -t security | grep -P "Chain|DROP"
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
    wg = lib.getExe pkgs.wireguard-tools;
    dns-root-hints = "${pkgs.dns-root-hints}/root.hints";
    wan-interface = "ve-vpn-eth1";
    br-interface = cfg.vpn.interfaces.bridge.name;
    br-network = lib.concatStringsSep "/" [
      cfg.vpn.interfaces.bridge.address
      (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
    ];
  in
    lib.mkIf cfg.enable
    # HOST CONFIGURATION
    {
      boot.kernel.sysctl = {
        # enables packet logging in containers
        "net.netfilter.nf_log_all_netns" = lib.mkDefault true;
        # increases the maximum number of packets queued to match so-rcvbuf
        "net.core.rmem_max" = 1048576;
      };

      # fixes permissions and the sgid not applying
      systemd.tmpfiles.rules = [
        "d /var/lib/servarr/redis-unbound-cachedb 2770 servarr servarr - -"
        "d /var/lib/servarr/redis-unbound-cachedb/appendonlydir 2770 servarr servarr - -"
      ];

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

      # FIXME: syslog rollup

      # systemd.network = {
      #   enable = true;
      #   networks = {
      #     "20-${br-interface}.network" = {
      #       matchConfig = {
      #         Name = br-interface;
      #       };
      #       networkConfig = {
      #         Bridge = "yes";
      #       };
      #     };
      #   };
      # };

      # CONTAINER CONFIGURATION
      containers = {
        # VPN CONTAINER
        servarr-vpn = let
          privateKeyFile = "/run/secrets/servarr/vpn/private.key";
          lan-interface = "ve-vpn-eth0";
          br-address = lib.concatStringsSep "/" [
            (offsetIpv4Address cfg.vpn.interfaces.bridge.address 1)
            (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
          ];
          wg-interface = "wg0";
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
                localAddress = br-address;
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
              # persists the unbound cache between reboots
              {
                "/var/lib/redis-unbound-cachedb/appendonlydir" = {
                  hostPath = "/var/lib/servarr/redis-unbound-cachedb/appendonlydir";
                  isReadOnly = false;
                };
              }
            ];
            config = {
              config,
              pkgs,
              lib,
              ...
            }: {
              config = {
                system.stateVersion = stateVersion;

                environment.systemPackages =
                  (with pkgs.bind; [dnsutils host])
                  ++ (with pkgs; [knot-dns tcpdump]);

                users = {
                  groups = {
                    inherit (cfg'.users.groups) servarr unbound redis-unbound-cachedb;
                  };
                  users = {
                    inherit (cfg'.users.users) servarr unbound redis-unbound-cachedb;
                  };
                };

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
                      # ${iptables} -t nat -I PREROUTING -s ${br-network} -j RETURN
                      ${iptables} -A OUTPUT -o ${wg-interface} -p udp --dport 53 -j DROP
                      ${iptables} -A OUTPUT -o ${wg-interface} -p tcp --dport 53 -j DROP
                    '';
                    # cleans up rule(s) and prevents failures when recovering from a broken state
                    extraStopCommands = ''
                      # ${iptables} -t nat -D PREROUTING -s ${br-network} -j RETURN
                      ${iptables} -D OUTPUT -o ${wg-interface} -p udp --dport 53 -j DROP || true
                      ${iptables} -D OUTPUT -o ${wg-interface} -p tcp --dport 53 -j DROP || true
                    '';
                  };

                  # forwards and nats all traffic from the bridge over the wireguard interface
                  nat = {
                    enable = true;
                    externalInterface = wg-interface;
                    internalInterfaces = [lan-interface];
                    # internalIPs = [br-network];
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
                  wireguard.interfaces = let
                    persistentKeepalive = 25;
                  in {
                    "${wg-interface}" = {
                      ips = cfg.vpn.address;
                      listenPort = cfg.vpn.endpoint.port;
                      inherit privateKeyFile;
                      peers = [
                        {
                          endpoint = "${cfg.vpn.endpoint.address}:${builtins.toString cfg.vpn.endpoint.port}";
                          inherit (cfg.vpn) publicKey;
                          inherit persistentKeepalive;
                          allowedIPs = ["0.0.0.0/1" "128.0.0.0/1"]; # force default route traffic through VPN
                        }
                      ];
                      postSetup = ''
                        ${wg} set ${wg-interface} peer ${cfg.vpn.publicKey} \
                          persistent-keepalive ${builtins.toString persistentKeepalive}
                      '';
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

                  services = {
                    "watchdog@wireguard-${wg-interface}" = {
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
                        ${lib.getExe' pkgs.knot-dns "kdig"} \
                          +tls @208.67.222.222 @208.67.220.220 myip.opendns.com A +short | grep -F "${prefix}"
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

                    # fixes the redis modules systemd config
                    redis-unbound-cachedb.serviceConfig = {
                      # adds automatic restarts
                      Restart = "on-failure";
                      RestartSec = "5s";
                      StateDirectoryMode = lib.mkForce "2770";
                      # RuntimeDirectoryMode = "0750";
                      # UMask = "0077";
                    };
                  };
                };

                services = let
                  cache-query-timeout = 300;
                in {
                  redis = {
                    # redis-cli -s /run/redis-unbound-cachedb/redis.sock
                    #  KEYS *
                    package = pkgs.valkey;
                    vmOverCommit = true;
                    servers = {
                      unbound-cachedb = {
                        enable = true;
                        # limits clients to unbound and a debug client
                        maxclients = 2;
                        # saves every x queries in y seconds
                        save = [[900 1] [300 10] [60 10000]];
                        # sets the maximum number of databases
                        databases = 1;
                        # disables rewriting persisted files; uses new files and deletes old ones
                        appendOnly = true;
                        # configures extra settings
                        settings = {
                          # disables remote connections
                          protected-mode = true;
                          # sets the memory cap
                          maxmemory = "128mb";
                          # keeps most recently resolved records
                          maxmemory-policy = "allkeys-lru";
                          # sets the query timeout
                          timeout = cache-query-timeout;
                        };
                      };
                    };
                  };
                  unbound = {
                    # ss -tuln
                    # dig @127.0.0.1 nixos.org
                    # dig @10.100.1.1 nixos.org
                    # tcpdump -tttt -n -q -c 100 -i any -vvv -s 0
                    # kdig @9.9.9.9 google.com
                    # echo "FILTER"; sudo iptables -L -v -n --line-numbers -t filter     | grep -P "Chain|DROP"
                    # echo "NAT"; sudo iptables -L -v -n --line-numbers -t nat           | grep -P "Chain|DROP"
                    # echo "MANGLE"; sudo iptables -L -v -n --line-numbers -t mangle     | grep -P "Chain|DROP"
                    #
                    # iptables -I INPUT -j LOG --log-prefix "INPUT: " --log-level 6
                    # iptables -I FORWARD -j LOG --log-prefix "FORWARD: " --log-level 6
                    # iptables -I OUTPUT -p udp --dport 53 -j LOG --log-prefix "OUTPUT DROP: " --log-level 6
                    # iptables -I OUTPUT -p tcp --dport 53 -j LOG --log-prefix "OUTPUT DROP: " --log-level 6
                    # iptables -I OUTPUT -j LOG --log-prefix "OUTPUT: " --log-level 6
                    # iptables -I nixos-fw-log-refuse -j LOG --log-prefix "INPUT DROP: " --log-level 6
                    #
                    # iptables -t nat -I PREROUTING -j LOG --log-prefix "NAT PREROUTING: " --log-level 6
                    # iptables -t nat -I INPUT -j LOG --log-prefix "NAT INPUT: " --log-level 6
                    # iptables -t nat -I OUTPUT -j LOG --log-prefix "NAT OUTPUT: " --log-level 6
                    # iptables -t nat -I POSTROUTING -j LOG --log-prefix "NAT POSTROUTING: " --log-level 6
                    # iptables -t nat -I nixos-nat-pre -j LOG --log-prefix "NAT MARK: " --log-level 6
                    # iptables -t nat -I nixos-nat-post -j LOG --log-prefix "NAT ROUTE MARKED: " --log-level 6
                    #
                    # iptables -t mangle -I nixos-fw-rpfilter -j LOG --log-prefix "MANGLE INPUT: " --log-level 6
                    # iptables -t mangle -I nixos-fw-rpfilter 5 -j LOG --log-prefix "MANGLE DROP: " --log-level 6
                    enable = true;
                    package = pkgs.unbound-full;
                    stateDir = "/run/unbound";
                    localControlSocketPath = "/run/unbound/unbound.ctl";
                    settings = {
                      server = {
                        module-config = ''"validator cachedb iterator"'';
                        # sets the interfaces to bind to
                        interface = [
                          "127.0.0.1"
                          (offsetIpv4Address cfg.vpn.interfaces.bridge.address 1)
                        ];
                        # sets which hosts can use this resolver
                        access-control = [
                          "127.0.0.0/8 allow"
                          "${br-network} allow"
                        ];
                        # forces the use of DNS over TLS for upstream queries
                        tls-upstream = true;
                        # sets the root nameserver names and addresses only
                        root-hints = dns-root-hints;
                        # trusts glue only if it is within the server's authority
                        harden-glue = true;
                        # requires dnssec data for trust-anchored zones, if such data is absent, the zone becomes bogus
                        harden-dnssec-stripped = true;
                        # hardens against algorithm downgrade when multiple algorithms are advertised in the DS record
                        harden-algo-downgrade = true;
                        # randomizes capitalization in the query to foil spoof attempts
                        use-caps-for-id = true;
                        # sends minimum amount of information to upstream servers to enhance privacy
                        qname-minimisation = true; # privacy enhancement
                        # reduces EDNS reassembly buffer size to reduce fragmentation reassembly problems
                        edns-buffer-size = 1420; # wg-interface mtu
                        # performs prefetching for domains that have been frequently queried
                        prefetch = true;
                        # sets the number of threads to create to serve clients
                        num-threads = 1;
                        # ensures kernel buffer is large enough to not lose messages in traffic spikes
                        so-rcvbuf = "1m";
                        # enables queries from localhost to be answered
                        do-not-query-localhost = false;
                        # ensures privacy of local ip ranges
                        private-address = [
                          "10.0.0.0/8" # private addresses
                          "127.0.0.0/8" # loopback addresses
                          "169.254.0.0/16" # link-local addresses
                          "172.16.0.0/12" # private addresses
                          "192.168.0.0/16" # private addresses
                          "::ffff:0:0/96" # IPv4 mapped addresses
                          "fd00::/8" # private addresses
                          "fe80::/10" # link-local addresses
                        ];
                        # FIXME: logging
                        log-time-ascii = true;
                        log-queries = true;
                        log-replies = true;
                        log-tag-queryreply = true;
                        log-destaddr = true;
                        log-local-actions = true;
                        log-servfail = true;
                        verbosity = 5;
                        val-log-level = 2;
                      };
                      forward-zone = {
                        # all dns queries are forwarded to the upstream servers
                        name = ".";
                        # requires DNS over TLS for upstream queries
                        forward-tls-upstream = "yes";
                        # sets upstream resolvers to use for forwarding
                        forward-addr = [
                          "9.9.9.9@853#dns.quad9.net"
                          "149.112.112.112@853#dns.quad9.net"
                          "8.8.8.8@853#dns.google"
                          "8.8.4.4@853#dns.google"
                          "1.1.1.1@853#cloudflare-dns.com"
                          "1.0.0.1@853#cloudflare-dns.com"
                          "208.67.222.222@853" # has multiple hostnames
                          "208.67.220.220@853" # has multiple hostnames
                        ];
                      };
                      remote-control = {
                        # enables the cli tool
                        control-enable = true;
                      };
                      # configure persistence # FIXME: impermanence
                      cachedb = {
                        # sets the back-end database
                        backend = "redis";
                        # creates a unix socket for client connections
                        redis-server-path = config.services.redis.servers.unbound-cachedb.unixSocket;
                        # sets the query timeout
                        redis-timeout = cache-query-timeout;
                        # configures records to be cleaned up
                        redis-expire-records = true;
                      };
                    };
                  };
                };
              };
            };
          };

        # VPN TEST CONTAINER
        servarr-test = let
          lan-interface = "ve-test-eth0";
          br-address = lib.concatStringsSep "/" [
            (offsetIpv4Address cfg.vpn.interfaces.bridge.address 2)
            (builtins.toString cfg.vpn.interfaces.bridge.prefixLength)
          ];
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
                localAddress = br-address;
              };
            };
            config = {
              pkgs,
              lib,
              ...
            }: {
              system.stateVersion = stateVersion;

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
