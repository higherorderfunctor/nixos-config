{
  inputs,
  lib,
  pkgs,
  ...
}: let
  hyprlock = lib.getExe pkgs.hyprlock;
  hyprctl = "${pkgs.hyprland}/bin/hyprctl";
  loginctl = "${pkgs.systemd}/bin/loginctl";
  systemctl = "${pkgs.systemd}/bin/systemctl";
  brightnessctl = lib.getExe pkgs.brightnessctl;
in {
  imports = [
    # FIXME: added to home manager
    #   https://github.com/nix-community/home-manager/pull/5324https://github.com/nix-community/home-manager/pull/5324
    #   I dont see in the option search so leaving fow now
    inputs.hypridle.homeManagerModules.default
  ];

  services.hypridle = {
    enable = true;
    package = pkgs.hypridle;
    #settings = {
    # general = {
    lockCmd = "pidof ${hyprlock} || ${hyprlock}"; # avoid starting multiple hyprlock instances
    beforeSleepCmd = "${loginctl} lock-session"; # lock before suspend
    afterSleepCmd = "${hyprctl} dispatch dpms on"; # to avoid having to press a key twice to turn on the display
    #};
    listeners = [
      {
        timeout = 150; # 2.5min.
        onTimeout = "${brightnessctl} -s set 10"; # set monitor backlight to minimum, avoid 0 on OLED monitor.
        onResume = "${brightnessctl} -r"; # monitor backlight restore.
      }
      {
        timeout = 150; # 2.5min.
        onTimeout = "${brightnessctl} -sd rgb:kbd_backlight set 0"; # turn off keyboard backlight.
        onResume = "${brightnessctl} -rd rgb:kbd_backlight"; # turn on keyboard backlight.
      }
      {
        timeout = 300; # 5min
        onTimeout = "${loginctl} lock-session"; # lock screen when timeout has passed
      }
      {
        timeout = 330; # 5.5min
        onTimeout = "${hyprctl} dispatch dpms off"; # screen off when timeout has passed
        onResume = "${hyprctl} dispatch dpms on"; # screen on when activity is detected after timeout has fired.
      }
      {
        timeout = 1800; # 30min
        onTimeout = "${systemctl} suspend"; # suspend pc
      }
    ];
    #};
  };
}
