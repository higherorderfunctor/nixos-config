_: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/sda";
}
