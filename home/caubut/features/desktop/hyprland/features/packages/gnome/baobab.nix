{pkgs, ...}: {
  # graphical application to analyse disk usage in any gnome environment # FIXME: not tested
  home.packages = [pkgs.baobab];
}
