{...}: {
  imports = [
    ./hardware-configuration.nix
    ./disk-config.nix
    ../common/global
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/sda";
}
