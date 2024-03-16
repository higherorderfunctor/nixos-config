{pkgs, ...}: {
  home = {
    packages = with pkgs; [
      nerdfonts # patched fonts with icons
      wl-clipboard # copy/paste utility for wayland
      dconf # config backend for gnome
      xdg-utils # gnome utlities like xdg-open
    ];
  };
}
# TODO: https://github.com/hyprwm/hyprpicker
