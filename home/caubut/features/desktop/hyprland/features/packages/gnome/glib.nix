{pkgs, ...}: {
  #  gnome system libraries like gio - test with nerd-tree delete to trash
  home.packages = [pkgs.glib];
}
