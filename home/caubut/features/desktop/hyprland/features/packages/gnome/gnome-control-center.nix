{pkgs, ...}: {
  # settings app
  home.packages = [pkgs.gnome-control-center];
  xdg.desktopEntries."org.gnome.Settings" = {
    name = "Settings";
    comment = "Gnome Control Center";
    icon = "org.gnome.Settings";
    exec = "env XDG_CURRENT_DESKTOP=gnome ${pkgs.gnome-control-center}/bin/gnome-control-center";
    categories = ["X-Preferences"];
    terminal = false;
  };
}
# 14:16:33.7685             GLib-GIO[102977]:   ERROR: Settings schema 'org.gnome.shell.app-switcher' is not installed
# [1]    102977 trace trap (core dumped)  XDG_CURRENT_DESKTOP=gnome gnome-control-center
