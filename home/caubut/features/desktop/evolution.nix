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
