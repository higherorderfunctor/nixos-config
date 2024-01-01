_: {
  imports = [
    ./hardware-configuration
    ../common/global
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/sda";
}
