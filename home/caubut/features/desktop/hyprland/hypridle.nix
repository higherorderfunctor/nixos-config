{
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
  home.packages = with pkgs; [
    ddcutil
    ddcui
  ];
  services.hypridle = {
    enable = true;
    package = pkgs.hypridle;
    settings = {
      general = {
        lock_cmd = "pidof ${hyprlock} || ${hyprlock}"; # avoid starting multiple hyprlock instances
        before_sleep_cmd = "${loginctl} lock-session"; # lock before suspend
        after_sleep_cmd = "${hyprctl} dispatch dpms on"; # to avoid having to press a key twice to turn on the display
      };
      listener = [
        # screen dimming
        {
          timeout = 150; # 2.5min.
          on-timeout = "${brightnessctl} -s set 10"; # set monitor backlight to minimum, avoid 0 on OLED monitor.
          on-resume = "${brightnessctl} -r"; # monitor backlight restore.
        }
        # keyboard backlight
        {
          timeout = 150; # 2.5min.
          on-timeout = "${brightnessctl} -sd rgb:kbd_backlight set 0"; # turn off keyboard backlight.
          on-resume = "${brightnessctl} -rd rgb:kbd_backlight"; # turn on keyboard backlight.
        }
        # screen lock
        {
          timeout = 300; # 5min
          on-timeout = "${loginctl} lock-session"; # lock screen when timeout has passed
        }
        # screen off
        {
          timeout = 330; # 5.5min
          on-timeout = "${hyprctl} dispatch dpms off"; # screen off when timeout has passed
          on-resume = "${hyprctl} dispatch dpms on"; # screen on when activity is detected after timeout has fired.
        }
        # suspend
        {
          timeout = 1800; # 30min
          on-timeout = "${systemctl} suspend"; # suspend pc
        }
      ];
    };
  };
}
