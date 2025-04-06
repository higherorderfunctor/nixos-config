{pkgs, ...}: {
  xdg.mimeApps = {
    enable = true;
    defaultApplications = {
      "message/rfc822" = ["org.gnome.Evolution.desktop"];
      "text/calendar" = ["org.gnome.Evolution.desktop"];
      "x-scheme-handler/mailto" = ["org.gnome.Evolution.desktop"];
    };
  };
  home.packages = with pkgs; [
    evolutionWithPlugins
    evolution-ews
  ];
}
# (WebKitWebProcess:2): Gdk-WARNING **: 13:55:54.751: Failed to read portal settings: GDBus.Error:org.freedesktop.DBus.Error.UnknownMethod: No such interface “org.freedesktop.portal.Settings” on object at path /org/freedesktop/portal/desktop
