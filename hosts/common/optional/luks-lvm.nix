# {disk ? "/dev/nvme0n1", ...}: {
_: {
  disko.devices = {
    disk = {
      root = {
        # device = disk;
        type = "disk";
        content = {
          type = "gpt";
          # TODO: preCreateHook = "nix run --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config#nvme-lbaf"; # TODO: setup
          partitions = {
            ESP = {
              type = "EF00"; # EFI partition type
              size = "2048M";
              content = {
                type = "filesystem";
                format = "vfat";
                mountpoint = "/boot";
                mountOptions = [
                  "defaults"
                ];
              };
            };
            luks = {
              size = "100%";
              content = {
                type = "luks";
                name = "cryptlvm";
                content = {
                  type = "lvm_pv"; # LVM physical volume
                  vg = "pool";
                };
              };
            };
          };
        };
      };
    };
    lvm_vg = {
      pool = {
        type = "lvm_vg"; # LVM volume group
        lvs = {
          root = {
            size = "100%FREE";
            content = {
              type = "filesystem";
              format = "ext4";
              mountpoint = "/";
              # TODO: postCreateHook = "lvreduce -L -256MB SystemVolGroup/root";
              mountOptions = [
                "defaults"
              ];
            };
          };
        };
      };
    };
  };
}
# TODO: secure boot
# TODO: tpm key
# TODO: only-key
