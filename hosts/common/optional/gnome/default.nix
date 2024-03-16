{pkgs, ...}: {
  services = {
    # TODO: services.gnome.gnome-keyring.enable
    # TODO: https://github.com/Aylur/dotfiles/blob/ffd0a66743affabe0083cb6ac14ce10b7f549039/nixos/gnome.nix
    udev.packages = with pkgs; [gnome.gnome-settings-daemon];
    geoclue2.enable = true; # location services - used by gnome-calendar
    gnome = {
      gnome-browser-connector.enable = true; # gnome integrations with web browsers
      # gnome-keyring.enable = true;
      gnome-settings-daemon.enable = true;
    };
  };

  security = {
    polkit.enable = true;
    pam.services.ags = {};
  };
  # packages = [pkgs.gnomeExtensions.advanced-volume-control];
  environment.systemPackages = with pkgs;
  with gnome; [
    #gnome.adwaita-icon-theme
    #loupe
    #adwaita-icon-theme
    #nautilus
    #baobab
    # gnome-boxes
    # gnome-system-monitor
    # gnome-control-center
    # gnome-weather
    # gnome-clocks
    # gnome-software # for flatpak
    # # wl-gammactl
    # gnome-settings-daemon
    # wayshot
    # pavucontrol
    # brightnessctl
    # swww
  ];
  # services.xserver = {
  #   # displayManager.gdm.enable = true;
  #   desktopManager.gnome = {
  #     enable = true;
  #     # extraGSettingsOverridePackages = [
  #     #   pkgs.nautilus-open-any-terminal
  #     # ];
  #   };
  # };
}
