{pkgs, ...}: {
  services = {
    udev.packages = with pkgs; [gnome.gnome-settings-daemon]; # TODO: needed?
    geoclue2.enable = true; # location services - used by gnome-calendar
    gnome = {
      gnome-browser-connector.enable = true; # gnome integrations with web browsers
      gnome-settings-daemon.enable = true;
    };
  };

  security = {
    polkit.enable = true;
    pam.services.ags = {};
  };
}
