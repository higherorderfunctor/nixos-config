{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  # https://nixos.wiki/wiki/GNOME#Running_GNOME_programs_outside_of_GNOME
  # FIXME: https://github.com/NixOS/nixpkgs/issues/174099
  # systemctl --user status gnome-keyring.services
  #
  services = {
    udev.packages = with pkgs; [gnome.gnome-settings-daemon];
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
      # gnome-browser-connector.enable = true; # gnome integrations with web browsers # FIXME: pulls in whole gnome shell
      # Service designed to take care of the user’s security credentials, such as user names and passwords.
      #
      # This configures system components, but not a service for GNOME keyring, the GNOME keyring service is configured
      # under home-manager.
      gnome-keyring.enable = true;
      gnome-settings-daemon.enable = true; # gnome settings daemon
    };
  };
  # TODO: good repo for settings
  # https://github.com/matthewpi/nixos-config/blob/38ebf6fee440ed4e745b178bac245300fadf2491/modules/hyprland/gsettings.nix

  # Enable hyprlock PAM (and gnome-keyring integration)
  #
  # Won't do anything until https://github.com/hyprwm/hyprlock/issues/4#issuecomment-1960904526 is resolved.
  # security.pam.services.hyprlock.enableGnomeKeyring = lib.mkDefault config.services.gnome.gnome-keyring.enable;

  # FIXME:
  # Mar 22 18:58:28 beelink-ser7 agent[2865]: Geolocation service not in use
  # Mar 22 18:58:30 beelink-ser7 .geoclue-wrappe[13975]: Failed to connect to avahi service: Daemon not running
  # Mar 22 18:58:30 beelink-ser7 agent[2865]: Geolocation service in use
  # Mar 22 18:58:31 beelink-ser7 .geoclue-wrappe[13975]: Failed to query location: No WiFi networks found
  # Mar 22 18:58:52 beelink-ser7 agent[2865]: Geolocation service not in use
  #  caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl status | grep dbus
  #           │ ├─dbus.service
  #           │ │ └─1527 /nix/store/f9w2kp8y55zvcyz33b5lnr7qwhx652y8-dbus-1.14.10/bin/dbus-daemon --system --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
  #                 │ ├─dbus.service
  #                 │ │ └─3219 /nix/store/f9w2kp8y55zvcyz33b5lnr7qwhx652y8-dbus-1.14.10/bin/dbus-daemon --session --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
  #                 │ └─38204 grep -i --color=auto dbus
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl status | grep portal
  #                 │ └─xdg-desktop-portal-gtk.service
  #                 │   └─3338 /nix/store/z8jcgkp8vy51gzd1map5wj1ppdkwxvzl-xdg-desktop-portal-gtk-1.15.1/libexec/xdg-desktop-portal-gtk
  #                 │ ├─xdg-desktop-portal-hyprland.service
  #                 │ │ └─3382 /nix/store/ibj971mkvcv2dqzfg4v5dkzr625dr2ya-xdg-desktop-portal-hyprland-1.3.1+date=2024-03-01_2d2fb54/libexec/xdg-desktop-portal-hyprland
  #                 │ ├─xdg-desktop-portal.service
  #                 │ │ └─35048 /nix/store/px78aqkcxncqq9hd99ylva44nb6qxp1n-xdg-desktop-portal-1.18.2/libexec/xdg-desktop-portal
  #                 │ ├─xdg-document-portal.service
  #                 │ │ ├─3324 /nix/store/px78aqkcxncqq9hd99ylva44nb6qxp1n-xdg-desktop-portal-1.18.2/libexec/xdg-document-portal
  #                 │ │ └─3335 fusermount3 -o rw,nosuid,nodev,fsname=portal,auto_unmount,subtype=portal -- /run/user/1000/doc
  #                 │   └─3328 /nix/store/px78aqkcxncqq9hd99ylva44nb6qxp1n-xdg-desktop-portal-1.18.2/libexec/xdg-permission-store
  #                 │ ├─28993 systemctl --user status xdg-desktop-portal
  #                 │ └─38242 grep -i --color=auto portal
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  journal^Asystemcl -
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl status xdg-desktop-portal-hyprland
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl --user status xdg-desktop-portal-hyprland
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl --user status xdg-desktop-portal
  # caubut@beelink-ser7 ~/..../nixos-config  dotfiles  systemctl --user status xdg-desktop-portal-gtk

  services = {
    # xserver = {
    #   enable = true;
    #   excludePackages = [pkgs.xterm];
    # };
    printing.enable = true;
    flatpak.enable = true;
  };

  # TODO: clean up
  # services.xserver.displayManager.startx.enable = true;

  programs.hyprland = {
    enable = true;
    package = pkgs.hyprland;
    # xwayland.enable = true;
  };

  xdg.portal = {
    enable = true; # required for flatpak even though enabled by home manager
    config.common.default = "gtk";
    extraPortals = with pkgs; [
      xdg-desktop-portal-gtk # required to enable the portal
    ];
  };
  # TODO: GDK_BACKEND=x11

  # review options
  # FIXME: https://github.com/fufexan/dotfiles/blob/15b42970336a81d40d8ec0f464a2f8662891c813/system/core/security.nix#L48
  security = {
    polkit.enable = true;
    pam.services = {
      ags = {};
      # Enable hyprlock PAM (and gnome-keyring integration)
      hyprlock.enableGnomeKeyring = lib.mkDefault config.services.gnome.gnome-keyring.enable;
      # allow wayland lockers to unlock the screen
      # hyprlock.text = "auth include login";
      hyprland.enableGnomeKeyring = true;
    };
  };

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
