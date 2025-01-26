# = vpn for containers
# FIXME: clean this up, initial hack up
# https://github.com/Faeranne/nix-config/blob/1fbc6a74f8296027458a3ccbb3771519d2ece930/services/media/tor.nix#L22
/*
sudo podman container list -a

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
  #  nv = (import ../../../overlays/nvpkgs.nix)."gluetun";
  nv = {
    pname = "gluetun";
    version = "latest";
    src = pkgs.dockerTools.pullImage {
      imageName = "qmcgaw/gluetun";
      imageDigest = "sha256:aaaf6c7c108f7f7caae978499b4cb823a135324992ce7cea4acd405a29298141";
      sha256 = "sha256-BTICvfWnHiU77CS4IkF63RyPQN4ZhX7c1wWNCMl6Oxc=";
      finalImageTag = "latest";
      os = "linux";
      arch = "amd64";
    };
  };
  mediaDir = "/var/lib/mediaserver";
  transmission = let
    transmission = pkgs.transmission_4;
    inherit (transmission) version;
    # https://github.com/transmission/transmission/blob/main/docs/Editing-Configuration-Files.md
    settings = builtins.toJSON {
      download-dir = "${mediaDir}/transmission/downloads";
      trash-can-enabled = false;
      message-level = 4;
      rpc-whitelist = "127.0.0.*,192.168.*.*,10.*.*.*";
    };
  in {
    autoStart = true;
    image = "transmission:${version}";
    imageFile = let
      nonRootShadowSetup = {
        user,
        uid,
        gid ? uid,
      }: [
        (
          pkgs.writeTextDir "etc/shadow" ''
            root:!x:::::::
            ${user}:!:::::::
          ''
        )
        (
          pkgs.writeTextDir "etc/passwd" ''
            root:x:0:0::/root:${pkgs.runtimeShell}
            ${user}:x:${toString uid}:${toString gid}::/home/${user}:
          ''
        )
        (
          pkgs.writeTextDir "etc/group" ''
            root:x:0:
            ${user}:x:${toString gid}:
          ''
        )
        (
          pkgs.writeTextDir "etc/gshadow" ''
            root:x::
            ${user}:x::
          ''
        )
      ];
    in
      # TODO: use users.transmission.uid and better tracking
      pkgs.dockerTools.buildLayeredImage {
        name = "transmission";
        tag = version;
        contents =
          nonRootShadowSetup {
            uid = 2001;
            user = "transmission";
          }
          ++ [
            pkgs.coreutils # TODO: move these to a base image so I can edit the config
            pkgs.jq
            pkgs.inotify-tools
            transmission
            (pkgs.writeTextDir "/etc/transmission/settings.json" settings)
            (
              pkgs.writeShellScriptBin "entrypoint" ''
                #!/usr/bin/env sh
                DEFAULT_SETTINGS_FILE=/etc/transmission/settings.json
                SETTINGS_FILE="${mediaDir}/transmission/config/settings.json"

                if [ ! -f "$SETTINGS_FILE" ]; then
                  echo '{}' > "$SETTINGS_FILE"
                fi

                mv "$SETTINGS_FILE" "$SETTINGS_FILE.bk"

                jq -s '.[0] * .[1]' "$DEFAULT_SETTINGS_FILE" "$SETTINGS_FILE.bk" > "$SETTINGS_FILE"

                /bin/transmission-daemon -g "${mediaDir}/transmission/config" -f &
                TRANSMISSION_PID=$!

                check_transmission_ready() {
                    echo "Checking if Transmission is ready..."
                    for i in {1..30}; do  # Try up to 30 times
                        if transmission-remote -l &> /dev/null; then
                            echo "Transmission is ready!"
                            return 0
                        else
                            echo "Waiting for Transmission to be ready..."
                            sleep 1
                        fi
                    done
                    echo "Failed to connect to Transmission."
                    exit 1
                }

                update_transmission_port() {
                    PORT=$(cat ${mediaDir}/gluetun/forwarded_port)
                    echo "Updating forwarding port to $PORT"
                    transmission-remote --port $PORT
                }

                check_transmission_ready
                update_transmission_port

                inotifywait -m ${mediaDir}/gluetun/forwarded_port -e modify -e moved_to -e create |
                while read path action file; do
                    echo "File '$file' at path '$path' had event '$action'"
                    update_transmission_port
                done &
                WATCH_PID=$!

                wait -n $TRANSMISSION_PID $WATCH_PID

                echo "One of the processes has exited. Exiting..."
                exit 1
              ''
            )
          ]
          ++ (with pkgs.dockerTools; [
            usrBinEnv
            binSh
            caCertificates
          ]);
        config = {
          Env = [
            "UID=2001"
            "GID=2001"
            "CURL_CA_BUNDLE=/etc/ssl/certs/ca-bundle.crt"
          ];
          User = "transmission:transmission";
          Entrypoint = [
            "/bin/entrypoint"
          ];
        };
        fakeRootCommands = ''
          set -x
          ls -la
          ls -la bin
          ls -la etc/transmission
          ls -la
          mkdir -p ./tmp
          chmod 777 ./tmp
          # chmod +x ./entrypoint
        '';
        # chown -R 2001:2001 ./var/run/transmission
      };
    # ports = [
    #   "127.0.0.1:9091:9091/tcp" # web-ui
    # ];
    volumes = [
      "${mediaDir}/transmission/config:${mediaDir}/transmission/config:rw"
      "${mediaDir}/transmission/downloads:${mediaDir}/transmission/downloads:rw"
      "${mediaDir}/gluetun:${mediaDir}/gluetun:ro"
    ];
    user = "transmission:transmission";
    dependsOn = ["gluetun"];
    extraOptions = [
      "--network=container:gluetun"
    ];
  };
in {
  #    my-transmission = pkgs.writeShellScriptBin "transmission" ''
  #    exec ${pkgs.transmission_4}/bin/transmission-daemon --foreground --log-level=info --config-dir ${./config-transmission}
  #  '';
  virtualisation.oci-containers.containers = {
    gluetun = {
      autoStart = true;
      image = "docker.io/${nv.src.imageName}@${nv.src.imageDigest}";
      ports = [
        "8888:8888/tcp" # HTTP proxy
        "8388:8388/tcp" # shadowsocks
        "8388:8388/udp" # shadowsocks
        "9091:9091/tcp" # transmission
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
        "${mediaDir}/gluetun:/tmp/gluetun:rw"
      ];
    };
    inherit transmission;
  };

  users = {
    groups = {
      media = {gid = 2000;};
      transmission = {gid = 2001;};
    };
    users = {
      media = {
        isSystemUser = true;
        uid = 2000;
        group = "media";
      };
      transmission = {
        isSystemUser = true;
        uid = 2001;
        group = "transmission";
        extraGroups = ["media"];
      };
    };
  };

  # systemd.tmpfiles.rules = [
  #   # TODO: gluetun to media group
  #   "d /var/run/gluetun 0755 root root -"
  # ];

  # TODO: issues using media group
  environment.persistence."/persist" = {
    directories = [
      {
        directory = "${mediaDir}/gluetun";
        mode = "0755";
      }
      {
        directory = "${mediaDir}/transmission/config";
        user = "2001";
        group = "2001";
        mode = "0775";
      }
      {
        directory = "${mediaDir}/transmission/downloads";
        user = "2001";
        group = "2001";
        mode = "0775";
      }
    ];
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
