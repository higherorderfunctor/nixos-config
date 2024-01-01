{...}: {
  imports = [
    ./hardware-configuration.nix
    ./disk-config.nix
    ../common/global
  ];

  # hostname
  networking.hostName = "vm";
}
