# {disk ? "/dev/nvme0n1", ...}: {
{
  inputs,
  lib,
  config,
  ...
}:
with lib; let
  cfg = config.root-luks-lvm-btrfs;
  # TODO: move to file
  rollback = ''
    mkdir /btrfs
    mount -t btrfs /dev/mapper/cryptlvm-root /btrfs

    # helper function to delete old snapshot(s)
    delete_subvolume_recursively() {
        IFS=$'\n'
        for i in $(btrfs subvolume list -o "$1" | cut -f 9- -d ' '); do
            delete_subvolume_recursively "/btrfs/$i"
        done
        btrfs subvolume delete "$1"
    }

    # backup last root
    if [[ -e /btrfs/root ]]; then
        mkdir -p /btrfs/snapshots/root
        timestamp=$(date --date="@$(stat -c %Y /btrfs/root)" "+%Y-%m-%d_%H:%M:%S")
        mv /btrfs/root "/btrfs/snapshots/root/$timestamp"
    fi

    # backup last home
    if [[ -e /btrfs/home ]]; then
        mkdir -p /btrfs/snapshots/home
        timestamp=$(date --date="@$(stat -c %Y /btrfs/home)" "+%Y-%m-%d_%H:%M:%S")
        mv /btrfs/home "/btrfs/snapshots/home/$timestamp"
    fi

    # delete anything older than 30 days but keep the last 5 regardless of age
    for i in $(find /btrfs/snapshots/root -maxdepth 1 -mtime +30 | sort | cut -d' ' -f2 | head -n -5); do
        delete_subvolume_recursively "$i"
    done
    for i in $(find /btrfs/snapshots/home -maxdepth 1 -mtime +30 | sort | cut -d' ' -f2 | head -n -5); do
        delete_subvolume_recursively "$i"
    done

    # restore blank root
    btrfs subvolume create /btrfs/root
    btrfs subvolume create /btrfs/home

    # clean up
    umount /btrfs
    rmdir /btrfs
  '';
in {
  imports = [
    inputs.disko.nixosModules.disko
  ];
  options.root-luks-lvm-btrfs = {
    device = mkOption {
      type = types.str;
    };
    swapSize = mkOption {
      type = types.str;
    };
  };

  config = {
    boot.initrd = {
      supportedFilesystems = ["btrfs"];
      # https://discourse.nixos.org/t/impermanence-vs-systemd-initrd-w-tpm-unlocking/25167/3
      # https://mt-caret.github.io/blog/posts/2020-06-29-optin-state.html
      postDeviceCommands = mkIf (!config.boot.initrd.systemd.enable) (mkBefore rollback);
      systemd.services.rollback = mkIf config.boot.initrd.systemd.enable {
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
          inherit (cfg) device;
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
                    mountOptions = ["compress=zstd" "noatime"];
                  };
                  "/nix" = {
                    # managed by this flake, os installed every boot
                    mountpoint = "/nix";
                    mountOptions = ["compress=zstd" "noatime"];
                  };
                  "/home" = {
                    # managed by home-manager
                    mountpoint = "/home";
                    mountOptions = ["compress=zstd" "noatime"];
                  };
                  "/swap" = {
                    mountpoint = "/.swapvol";
                    swap.swapfile.size = cfg.swapSize;
                  };
                };
              };
            };
          };
        };
      };
    };

    fileSystems = {
      "/home".neededForBoot = true;
      "/persist".neededForBoot = true;
    };

    boot.kernel.sysctl = {
      "vm.swappiness" = 1;
      "vm.vfs_cache_pressure" = 50;
    };
  };
}
# TODO: secure boot
# TODO: tpm key
# TODO: only-key
