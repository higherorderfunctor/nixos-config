{config, ...}: {
  imports = [
    ../common/optional/root-luks-lvm-btrfs.nix
  ];

  # configure the root device
  config.root-luks-lvm-btrfs = {
    device = "/dev/nvme0n1";
    swapSize = "8G";
  };
}
