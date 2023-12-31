{
  pkgs,
  inputs,
  ...
}: {
  imports = [
    #inputs.hardware.nixosModules.common-cpu-amd
    #inputs.hardware.nixosModules.common-pc-ssd
    ./hardware-configuration.nix

    ../common/global
  ];

  networking = {
    hostName = "beelink-ser7";
    useDHCP = true;
  };

  boot = {
    loader.systemd-boot.enable = true;
    loader.efi.canTouchEfiVariables = true;
    initrd.luks.devices = {
      ssd = "/dev/disk/by-label/dm-name-pool-root"; # TODO:
    };
  };

  # programs = {
  #   adb.enable = true;
  #   dconf.enable = true;
  #   kdeconnect.enable = true;
  # };

  # services.hardware.openrgb.enable = true;
  # hardware = {
  #   opengl.enable = true;
  #   opentabletdriver.enable = true;
  # };
}
#   boot.initrd = {
#     luks.devices."${hostname}".device = "/dev/disk/by-label/${hostname}_crypt";
#   };
#  imports = [
#    ./services
#    ./hardware-configuration.nix
#
#    ../common/global
#    ../common/users/misterio
#    ../common/optional/fail2ban.nix
#    ../common/optional/tailscale-exit-node.nix
#  ];
