_: {
  imports = [
    ../common/global
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";
}
