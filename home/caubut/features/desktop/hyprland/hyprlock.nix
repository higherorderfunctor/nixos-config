{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: let
  cfg = config.programs.hyprlock;
in {
  imports = [
    inputs.hyprlock.homeManagerModules.default
  ];

  # prevent defaults in favor of a package
  xdg.configFile."hypr/hyprlock.conf".text = lib.mkForce ''
    ${builtins.concatStringsSep "\n" (map (source: ''
        source = ${source}
      '')
      cfg.sources)}
  '';

  programs.hyprlock = {
    enable = true;
    package = pkgs.hyprlock;

    sources = [
      "${pkgs.catppuccin-hyprland}/mocha.conf"
      "${pkgs.catppuccin-hyprlock}/hyprlock.conf"
    ];
  };
}
