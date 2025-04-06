{pkgs, ...}: {
  # graphical application to analyse disk usage in any gnome environment # FIXME: not tested
  home.packages = [pkgs.baobab];
}
# FIXME: (baobab:23551): Adwaita-WARNING **: 22:42:33.819: AdwNavigationPage 0x203cae0 is missing a title. To hide a header bar title, consider using AdwHeaderBar:show-title instead.
