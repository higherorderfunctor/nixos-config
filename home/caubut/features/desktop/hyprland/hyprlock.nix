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

    # general = {
    #   disable_loading_bar = true;
    #   hide_cursor = false;
    #   no_fade_in = true;
    # };

    # backgrounds = [
    #   {
    #     monitor = "";
    #     # path = "${config.home.homeDirectory}/wall.png";
    #   }
    # ];

    # input-fields = [
    #   {
    #     monitor = "eDP-1";

    #     size = {
    #       width = 300;
    #       height = 50;
    #     };

    #     outline_thickness = 2;

    #     # outer_color = "rgb(${c.primary})";
    #     # inner_color = "rgb(${c.on_primary_container})";
    #     # font_color = "rgb(${c.primary_container})";

    #     fade_on_empty = false;
    #     # placeholder_text = ''<span font_family="${font_family}" foreground="##${c.primary_container}">Password...</span>'';
    #     placeholder_text = ''<span>Password...</span>'';

    #     dots_spacing = 0.3;
    #     dots_center = true;
    #   }
    # ];

    # labels = [
    #   {
    #     monitor = "";
    #     text = "$TIME";
    #     # inherit font_family;
    #     font_size = 50;
    #     # color = "rgb(${c.primary})";

    #     position = {
    #       x = 0;
    #       y = 80;
    #     };

    #     valign = "center";
    #     halign = "center";
    #   }
    # ];
  };
}
