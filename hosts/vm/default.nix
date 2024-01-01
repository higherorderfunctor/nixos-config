{...}: {
  imports = [
    ../common/optional/minimal-x86_64-linux-hardware-configuration.nix
    ./disk-config.nix
    ../common/global
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";
}
