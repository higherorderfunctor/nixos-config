{pkgs, ...}: {
  services = {
    udev.packages = with pkgs; [gnome.gnome-settings-daemon]; # TODO: needed?
    geoclue2.enable = true; # location services - used by gnome-calendar
    gvfs.enable = true; # user space vfs used by gio
    gnome = {
      evolution-data-server.enable = true;
      glib-networking.enable = true;
      gnome-browser-connector.enable = true; # gnome integrations with web browsers
      gnome-keyring.enable = true;
      gnome-settings-daemon.enable = true;
      # gnome-online-accounts.enable = true;
    };
  };

  security = {
    polkit.enable = true;
    pam.services.ags = {};
  };
}
# TODO:
# services = {
#   devmon.enable = true;
#   udisks2.enable = true;
#   upower.enable = true;
#   power-profiles-daemon.enable = true;
#   accounts-daemon.enable = true;
# };
