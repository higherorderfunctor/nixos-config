{
  config,
  lib,
  pkgs,
  ...
}: {
  imports = [
    ../../global
    ../../features/cli/nix.nix
    ../../features/system/nix-gl-host.nix
    ../../features/desktop
    ../../features/system/openconnect.nix
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
  # fix for non-nixos systems
  targets.genericLinux.enable = true;

  # TODO:
  home.packages = with pkgs; [gnome-network-displays];

  # GTK theme
  # gtk = {
  #   enable = true;
  #   gtk3.extraConfig = {
  #     "gtk-application-prefer-dark-theme" = 1;
  #   };
  #   gtk4.extraConfig = {
  #     "gtk-application-prefer-dark-theme" = 1;
  #   };
  #   # font
  #   font = {
  #     name = "Ubuntu Nerd Font Regular";
  #   };
  #   # icon theme
  #   # iconTheme = {
  #   #   name = "Vivid-Glassy-Dark-Icons";
  #   #   package = pkgs.vivid-icons-themes;
  #   # };
  #   # decorations theme
  #   theme = {
  #     name = "catppuccin-mocha-red-compact+rimless,black";
  #     package =
  #       pkgs.catppuccin-gtk.override
  #       {
  #         accents = ["sky" "red"];
  #         size = "compact";
  #         tweaks = ["rimless" "black"];
  #         variant = "mocha";
  #       };
  #   };
  # };
  # xdg.configFile = {
  #   "gtk-4.0/assets".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-4.0/assets";
  #   "gtk-4.0/gtk.css".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-4.0/gtk.css";
  #   "gtk-4.0/gtk-dark.css".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-4.0/gtk-dark.css";
  #   "gtk-3.0/assets".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-3.0/assets";
  #   "gtk-3.0/gtk.css".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-3.0/gtk.css";
  #   "gtk-3.0/gtk-dark.css".source = "${config.gtk.theme.package}/share/themes/${config.gtk.theme.name}-dark/gtk-3.0/gtk-dark.css";
  # };
}
