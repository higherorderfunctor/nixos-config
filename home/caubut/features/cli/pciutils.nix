{pkgs, ...}: {
  home.packages = [pkgs.pciutils pkgs.usbutils]; # TODO
}
