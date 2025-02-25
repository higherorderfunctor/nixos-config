{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.services.nixos-config;
in {
  options.services.xwaylandvideobridge = {
    enable = lib.mkEnableOption "nixos-config";
  };
  config.systemd.user.services.xwaylandvideobridge = lib.mkIf cfg.enable {
    Unit = {
      Description = "Utility to allow streaming Wayland windows to X applications";
      Documentation = "https://invent.kde.org/system/xwaylandvideobridge";
    };
    Service.ExecStart = lib.getExe pkgs.kdePackages.xwaylandvideobridge;
    Install.WantedBy = ["graphical-session.target"];
  };
}
