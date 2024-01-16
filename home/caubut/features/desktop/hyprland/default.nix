{
  inputs,
  lib,
  pkgs,
  ...
}: {
  imports = [
    inputs.hyprland.homeManagerModules.default
  ];
  xdg.portal = {
    enable = true;
    extraPortals = [inputs.hyprland.packages.${pkgs.system}.xdg-desktop-portal-hyprland];
    configPackages = [inputs.hyprland.packages.${pkgs.system}.hyprland];
  };
  wayland.windowManager.hyprland = {
    enable = true;
    package = inputs.hyprland.packages.${pkgs.system}.hyprland;
    settings = {
      "$mod" = "SUPER";
      exec-once = "eww daemon";
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
