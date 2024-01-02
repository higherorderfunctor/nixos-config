{...}: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
  ];

  # hostname
  networking.hostName = "vm";
}
