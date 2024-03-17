{pkgs, ...}: {
  # contrast, brightness, and gamma adjustments for wayland # FIXME: not checked
  home.packages = [pkgs.wl-clipboard];
}
