{pkgs, ...}: {
  home.packages = [pkgs.pciutils pkgs.usbutils pkgs.lshw]; # TODO
}
