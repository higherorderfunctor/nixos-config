# {disk ? "/dev/nvme0n1", ...}: {
{
  lib,
  config,
  ...
}: let
  rollback = ''
    mkdir /btrfs
    mount -t btrfs /dev/mapper/cryptlvm-root /btrfs

    # backup last root
    if [[ -e /btrfs/root ]]; then
        mkdir -p /btrfs/snapshots
        timestamp=$(date --date="@$(stat -c %Y /btrfs/root)" "+%Y-%m-%-d_%H:%M:%S")
        mv /btrfs/root "/btrfs/snapshots/$timestamp"
    fi

    # delete old snapshot
    delete_subvolume_recursively() {
        IFS=$'\n'
        for i in $(btrfs subvolume list -o "$1" | cut -f 9- -d ' '); do
            delete_subvolume_recursively "/btrfs/$i"
        done
        btrfs subvolume delete "$1"
    }

    # delete anything older than 30 days
    for i in $(find /btrfs/snapshots/ -maxdepth 1 -mtime +30); do
        delete_subvolume_recursively "$i"
    done

    # restore blank root
    btrfs subvolume create /btrfs/root

    # clean up
    umount /btrfs
    rmdir /btrfs
  '';
in {
  boot.initrd = {
    supportedFilesystems = ["btrfs"];
    # https://discourse.nixos.org/t/impermanence-vs-systemd-initrd-w-tpm-unlocking/25167/3
    # https://mt-caret.github.io/blog/posts/2020-06-29-optin-state.html
    postDeviceCommands = lib.mkIf (!config.boot.initrd.systemd.enable) (lib.mkBefore rollback);
    systemd.services.rollback = lib.mkIf config.boot.initrd.systemd.enable {
      description = "Rollback BTRFS root subvolume to empty state";
      wantedBy = ["initrd.target"];
      after = [
        "systemd-cryptsetup@enc.service"
      ];
      before = ["sysroot.mount"];
      unitConfig.DefaultDependencies = "no";
      serviceConfig.Type = "oneshot";
      script = rollback;
    };
  };

  disko.devices = {
    disk = {
      root = {
        # device = ...; set by importer
        type = "disk";
        content = {
          type = "gpt";
          partitions = {
            ESP = {
              type = "EF00"; # EFI partition type
              size = "2048M";
              content = {
                type = "filesystem";
                format = "vfat";
                mountpoint = "/boot";
                mountOptions = [
                  "uid=0"
                  "gid=0"
                  "fmask=0077"
                  "dmask=0077"
                  "defaults"
                ];
              };
            };
            luks = {
              size = "100%";
              content = {
                type = "luks";
                name = "cryptlvm";
                settings = {
                  allowDiscards = true;
                };
                content = {
                  type = "lvm_pv"; # LVM physical volume
                  vg = "cryptlvm";
                };
              };
            };
          };
        };
      };
    };
    lvm_vg = {
      cryptlvm = {
        type = "lvm_vg"; # LVM volume group
        lvs = {
          root = {
            size = "100%FREE";
            content = {
              type = "btrfs";
              extraArgs = ["-f"];
              subvolumes = {
                "/root" = {
                  # wiped every boot
                  mountpoint = "/";
                  mountOptions = ["subvol=root" "compress=zstd" "noatime"];
                };
                "/persist" = {
                  # persistent data between boots
                  mountpoint = "/persist";
                  mountOptions = ["subvol=persist" "compress=zstd" "noatime"];
                };
                "/nix" = {
                  # managed by this flake, os installed every boot
                  mountpoint = "/nix";
                  mountOptions = ["subvol=nix" "compress=zstd" "noatime"];
                };
                "/etc/nixos" = {
                  # managed by this flake, os installed every boot
                  mountpoint = "/etc/nixos";
                  mountOptions = ["subvol=nix" "compress=zstd" "noatime"];
                };
                "/home" = {
                  # managed by home-manager
                  mountpoint = "/home";
                  mountOptions = ["compress=zstd" "noatime"];
                };
              };
            };
          };
        };
      };
    };
  };

  fileSystems."/persist".neededForBoot = true;
}
# TODO: secure boot
# TODO: tpm key
# TODO: only-key
