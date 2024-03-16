{pkgs, ...}: {
  # copy/paste utility for wayland # FIXME: not checked
  home.packages = [pkgs.wl-clipboard];
}
