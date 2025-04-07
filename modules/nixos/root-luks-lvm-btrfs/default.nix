{
  inputs,
  lib,
  config,
  ...
}:
with lib; let
  cfg = config.root-luks-lvm-btrfs2;
in {
  imports = [
    inputs.disko.nixosModules.disko
  ];

  options.root-luks-lvm-btrfs2 = {
    enable = lib.mkEnableOption {
      type = lib.types.bool;
      default = false;
    };
    device = lib.mkOption {
      type = lib.types.str;
    };
    swapSize = lib.mkOption {
      type = lib.types.str;
    };
    compression = lib.mkOption {
      type = lib.types.str;
      default = "zstd:1";
    };
  };

  config = mkIf cfg.enable {
    boot.kernel.sysctl = {
      "vm.swappiness" = 1;
      "vm.vfs_cache_pressure" = 50;
    };

    boot.initrd = {
      supportedFilesystems = ["btrfs"];

      # https://mt-caret.github.io/blog/posts/2020-06-29-optin-state.html

      # without systemd during stage-1
      postDeviceCommands = mkIf (!config.boot.initrd.systemd.enable) (mkBefore "${./scripts/btrfs-rollback}");

      # with systemd during stage-1
      systemd.services.rollback = mkIf config.boot.initrd.systemd.enable {
        systemd.services.btrfs-rollback = {
          Description = "Rollback BTRFS root subvolume to empty state";
          WantedBy = ["initrd.target"];
          After = [
            # https://discourse.nixos.org/t/impermanence-vs-systemd-initrd-w-tpm-unlocking/25167/3
            "initrd-root-device.target"
          ];
          Before = ["sysroot.mount"];
          UnitConfig.DefaultDependencies = "no";
          ServiceConfig.Type = "oneshot";
          Script = "${./scropts/btrfs-rollback}";
        };
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
                    mountOptions = ["subvol=root" "compress=${compression}" "noatime"];
                  };
                  "/persist" = {
                    # persistent data between boots
                    mountpoint = "/persist";
                    mountOptions = ["compress=${compression}" "noatime"];
                  };
                  "/nix" = {
                    # managed by this flake, os installed every boot
                    mountpoint = "/nix";
                    mountOptions = ["compress=${compression}" "noatime"];
                  };
                  "/home" = {
                    # managed by home-manager
                    mountpoint = "/home";
                    mountOptions = ["compress=${compression}" "noatime"];
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
  };
}
