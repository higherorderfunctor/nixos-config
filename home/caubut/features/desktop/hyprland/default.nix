{
  inputs,
  lib,
  pkgs,
  ...
}: {
  xdg.portal = {
    enable = true;
    extraPortals = [inputs.hyprland.xdg-desktop-portal-hyprland];
    configPackages = [inputs.hyprland.hyprland];
  };
  wayland.windowManager.hyprland = {
    enable = true;
    package = inputs.hyprland.packages.${pkgs.system}.hyprland;
    settings = {
      "$mod" = "SUPER";
    };
    systemd = {
      enable = true;
      # Same as default, but stop graphical-session too
      extraCommands = lib.mkBefore [
        "systemctl --user stop graphical-session.target"
        "systemctl --user start hyprland-session.target"
      ];
    };
  };
}