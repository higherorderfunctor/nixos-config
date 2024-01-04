_: {
  imports = [
    ../common/optional/root-luks-lvm-btrfs.nix
  ];

  # configure the root device
  config.rootLuksLvmBtrfs = {
    device = "/dev/nvme0n1";
    swapSize = "1G";
  };
}
