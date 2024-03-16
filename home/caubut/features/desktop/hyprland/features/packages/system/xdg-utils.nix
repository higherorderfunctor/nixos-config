{pkgs, ...}: {
  # gnome utlities like xdg-open
  home.packages = [pkgs.xdg-utils];
}
