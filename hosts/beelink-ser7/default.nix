{...}: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
    ../common/optional/openssh.nix
  ];

  # hostname
  networking.hostName = "beelink-ser7";
}
