{...}: {
  imports = [
    ../common/optional/root-luks-lvm-btrfs.nix
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";
}
