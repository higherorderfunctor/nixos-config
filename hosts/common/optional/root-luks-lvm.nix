# {disk ? "/dev/nvme0n1", ...}: {
{
  lib,
  config,
  ...
}: let
  rollback = ''
    mkdir /btrfs-tmp
    mount -t btrfs /dev/mapper/cryptlvm-root /btrfs-tmp

    if [[ -e /btrfs-tmp/root ]]; then
        mkdir -p /btrfs-tmp/old-roots
        timestamp=$(date --date="@$(stat -c %Y /btrfs-tmp/root)" "+%Y-%m-%-d_%H:%M:%S")
        mv /btrfs-tmp/root "/btrfs-tmp/old-roots/$timestamp"
    fi

    delete_subvolume_recursively() {
        IFS=$'\n'
        for i in $(btrfs subvolume list -o "$1" | cut -f 9- -d ' '); do
            delete_subvolume_recursively "/btrfs-tmp/$i"
        done
        btrfs subvolume delete "$1"
    }

    for i in $(find /btrfs-tmp/old-roots/ -maxdepth 1 -mtime +30); do
        delete_subvolume_recursively "$i"
    done

    btrfs subvolume create /btrfs-tmp/root
    umount /btrfs-tmp
  '';
  phase1Systemd = config.boot.initrd.systemd.enable;
in {
  boot.initrd = {
    supportedFilesystems = ["btrfs"];
    # https://discourse.nixos.org/t/impermanence-vs-systemd-initrd-w-tpm-unlocking/25167/3
    # https://mt-caret.github.io/blog/posts/2020-06-29-optin-state.html
    postDeviceCommands = lib.mkIf (!phase1Systemd) (lib.mkBefore rollback);
    systemd.services.rollback = lib.mkIf phase1Systemd {
      description = "Rollback btrfs rootfs";
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
                "/rootfs" = {
                  mountpoint = "/";
                  mountOptions = ["subvol=root" "compress=zstd" "noatime"];
                };
                "/persist" = {
                  mountpoint = "/persist";
                  bootable = true;
                  mountOptions = ["subvol=persist" "compress=zstd" "noatime"];
                };
                "/nix" = {
                  mountpoint = "/nix";
                  mountOptions = ["subvol=nix" "compress=zstd" "noatime"];
                };
                "/home" = {
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
