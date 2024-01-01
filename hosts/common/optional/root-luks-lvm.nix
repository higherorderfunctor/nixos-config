# {disk ? "/dev/nvme0n1", ...}: {
_: {
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
                content = {
                  type = "lvm_pv"; # LVM physical volume
                  vg = "cryptpool";
                };
              };
            };
          };
        };
      };
    };
    lvm_vg = {
      cryptpool = {
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
