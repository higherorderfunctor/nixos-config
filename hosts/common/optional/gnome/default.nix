{pkgs, ...}: {
  services = {
    # udev.packages = with pkgs; [gnome.gnome-settings-daemon]; # TODO: needed?
    accounts-daemon.enable = true; # dbus service for accessing the list of user accounts and information attached to those accounts
    devmon.enable = true; # automatic device mounting daemon
    geoclue2.enable = true; # dbus service that provides location information for accessing - used by gnome-calendar
    gvfs.enable = true; # userspace virtual filesystem
    power-profiles-daemon.enable = true; # dbus daemon that allows changing system behavior based upon user-selected power profiles
    udisks2.enable = true; # dbus service allowing applications to query and manipulate storage
    upower.enable = true; # dbus service that provides power management support to applications
    gnome = {
      evolution-data-server.enable = true; # collection of services for storing addressbooks and calendars
      glib-networking.enable = true; # network extensions for glib
      gnome-browser-connector.enable = true; # gnome integrations with web browsers
      gnome-keyring.enable = true; # service designed to take care of the user’s security credentials, such as user names and passwords
      gnome-settings-daemon.enable = true; # gnome settings daemon
    };
  };

  # FIXME:
  # Mar 22 18:58:28 beelink-ser7 agent[2865]: Geolocation service not in use
  # Mar 22 18:58:30 beelink-ser7 .geoclue-wrappe[13975]: Failed to connect to avahi service: Daemon not running
  # Mar 22 18:58:30 beelink-ser7 agent[2865]: Geolocation service in use
  # Mar 22 18:58:31 beelink-ser7 .geoclue-wrappe[13975]: Failed to query location: No WiFi networks found
  # Mar 22 18:58:52 beelink-ser7 agent[2865]: Geolocation service not in use

  services = {
    xserver = {
      enable = true;
      excludePackages = [pkgs.xterm];
    };
    printing.enable = true;
    flatpak.enable = true;
  };

  xdg.portal = {
    enable = true; # required for flatpak even though enabled by home manager
    config.common.default = "gtk";
    extraPortals = with pkgs; [
      xdg-desktop-portal-gtk # required to enable the portal
    ];
  };
  # TODO: GDK_BACKEND=x11

  security = {
    polkit.enable = true;
    pam.services.ags = {};
  };

  # TODO: clean up
  services.xserver.displayManager.startx.enable = true;

  systemd = {
    user.services.polkit-gnome-authentication-agent-1 = {
      description = "polkit-gnome-authentication-agent-1";
      wantedBy = ["graphical-session.target"];
      wants = ["graphical-session.target"];
      after = ["graphical-session.target"];
      serviceConfig = {
        Type = "simple";
        ExecStart = "${pkgs.polkit_gnome}/libexec/polkit-gnome-authentication-agent-1";
        Restart = "on-failure";
        RestartSec = 1;
        TimeoutStopSec = 10;
      };
    };
  };
}
