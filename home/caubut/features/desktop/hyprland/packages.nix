{pkgs, ...}: {
  home = {
    packages = with pkgs;
    with gnome; [
      dconf # config backend for gnome
      glib # gnome system libraries like gio
      gnome-calculator # calendar app
      gnome-calendar # calculator app
      nerdfonts # patched fonts with icons
      wl-clipboard # copy/paste utility for wayland
      xdg-utils # gnome utlities like xdg-open
    ];
  };
}
# TODO: https://github.com/hyprwm/hyprpicker
