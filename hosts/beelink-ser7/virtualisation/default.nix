# = vpn for containers
/*
sudo podman container list -a
systemctl status podman-gluetun

systemctl status podman-gluetun
sudo podman logs -f gluetun
sudo podman restart gluetun
sudo podman exec -it gluetun /bin/sh

systemctl status podman-transmission
sudo podman logs -f transmission
sudo podman restart transmission
sudo podman exec -it transmission /bin/sh
*/
{
  config,
  pkgs,
  ...
}: let
  nv = (import ../../../overlays/nvpkgs.nix)."gluetun";
in {
  #    my-transmission = pkgs.writeShellScriptBin "transmission" ''
  #    exec ${pkgs.transmission_4}/bin/transmission-daemon --foreground --log-level=info --config-dir ${./config-transmission}
  #  '';
  virtualisation.oci-containers.containers = {
    gluetun = {
      image = "docker.io/${nv.src.imageName}@${nv.src.imageDigest}";
      autoStart = true;
      ports = [
        "127.0.0.1:8888:8888/tcp" # HTTP proxy
        "127.0.0.1:8388:8388/tcp" # shadowsocks
        "127.0.0.1:8388:8388/udp" # shadowsocks
      ];
      extraOptions = [
        "--cap-add=NET_ADMIN"
        "--device=/dev/net/tun"
      ];
      environmentFiles = [
        config.sops.secrets."gluetun.env".path
      ];
      volumes = [
        "${config.sops.secrets."wg0.conf".path}:/gluetun/wireguard/wg0.conf"
      ];
    };
    transmission = let
      transmission = pkgs.transmission_4;
      inherit (transmission) version;
    in {
      image = "transmission:${version}";
      imageFile = pkgs.dockerTools.buildLayeredImage {
        name = "transmission";
        tag = version;
        contents = [transmission];
      };
      dependsOn = ["gluetun"];
      extraOptions = [
        "--network=container:gluetun"
      ];
      autoStart = true;
    };
  };

  users = {
    groups = {
      media = {};
      transmission = {};
    };
    users = {
      transmission = {
        isSystemUser = true;
        group = "transmission";
        extraGroups = ["media"];
      };
    };
  };

  environment.persistence = {
    "/persist" = {
      hideMounts = true;
      directories = [
        {
          directory = "/var/lib/media";
          user = "media";
          group = "media";
          mode = "u=rwx,g=rx,o=";
        }
      ];
    };
  };

  # secrets
  sops.secrets = {
    "gluetun.env" = {
      mode = "400";
      format = "dotenv";
      sopsFile = ../secrets/gluetun.env;
    };
    "wg0.conf" = {
      mode = "400";
      format = "ini";
      sopsFile = ../secrets/wireguard.ini;
    };
  };
}
# {
#   sops.secrets."gluetun.env" = { };
#   virtualisation.oci-containers.containers = {
#     gluetun = {
#       image = "qmcgaw/gluetun:v3";
#       ports = [
#         "8388:8388/tcp" # Shadowsocks
#         "8388:8388/udp" # Shadowsocks
#       ];
#       extraOptions = [
#         "--cap-add=NET_ADMIN"
#       ];
#       environmentFiles = [
#         config.sops.secrets."gluetun.env".path
#       ];
#     };
#   };
#
#   networking.firewall = {
#     allowedTCPPorts = [
#       8388
#     ];
#     allowedUDPPorts = [
#       8388
#     ];
#   };
# }
/*
exec podman run \
  --rm \
  -it \
  --name='transmission' \
  --log-driver=journald \
  --cidfile=/run/podman-'transmission'.ctr-id \
  --cgroups=no-conmon \
  --sdnotify=conmon \
  -d \
  --replace \
  '--network=container:gluetun' \
  transmission:4.0.5
*/
