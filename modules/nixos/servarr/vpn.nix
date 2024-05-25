{
  config,
  lib,
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
    };
  };

  config = lib.mkIf cfg.enable {
    networking = {
      bridges.servarr-vpn-br0.interfaces = [
        "servarr-vpn"
        "servarr-test"
      ];
      interfaces = {
        ################
        servarr-gw0 = {
          virtual = true;
          ipv4.addresses = [
            {
              address = "10.100.0.0";
              prefixLength = 31;
            }
          ];
        };
        ################
        servarr-vpn = {
          virtual = true;
        };
        servarr-test = {
          virtual = true;
        };
      };
      nat = {
        enable = lib.mkDefault true;
        internalInterfaces = ["servarr-gw0"];
        #   externalInterface = "enp1s0";
      };
    };
    containers = {
      servarr-vpn = let
        privateKeyFile = "/run/secrets/servarr/vpn/private.key";
      in
        lib.mkIf cfg.vpn.enable {
          autoStart = true;
          ephemeral = true;
          restartIfChanged = true;
          interfaces = [
            "servarr-gw0"
            "servarr-vpn"
          ];
          # privateNetwork = true;
          # hostAddress = "192.168.200.0";
          # localAddress = "192.168.200.1";
          # extraVeths.ve-vpn = {
          #   hostBridge = "servarr-br0";
          #   # localAddress = "192.168.100.1";
          # };
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
            iptables = lib.getExe' pkgs.iptables "iptables";
            wg = lib.getExe pkgs.wireguard-tools;
            wg-interface = "wg0";
          in {
            system.stateVersion = config.system.stateVersion;

            networking = {
              firewall = {
                enable = true;
                interfaces = {
                  eth0 = {
                    allowedUDPPorts = [51820];
                  };
                };
              };
              # interfaces.eth0.ipv4.routes = [
              #   {
              #     address = "149.50.216.205";
              #     prefixLength = 32;
              #     via = "192.168.100.10";
              #   }
              # ];
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
        enableTun = true;
        ephemeral = true;
        restartIfChanged = true;
        interfaces = [
          "servarr-test"
        ];
        # privateNetwork = true;
        # # hostAddress = "192.168.100.1";
        # hostBridge = "servarr-br0";
        # localAddress = "192.168.100.2";
        config = {
          pkgs,
          lib,
          ...
        }: {
          system.stateVersion = config.system.stateVersion;

          networking = {
            defaultGateway = {
              interface = "ve-servarr-vpn-br0";
              address = "192.168.100.1";
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
