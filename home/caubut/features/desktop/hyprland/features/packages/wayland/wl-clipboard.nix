{pkgs, ...}: {
  # command-line copy/paste utilities for wayland # FIXME: not checked
  home.packages = [pkgs.wl-clipboard];
}
