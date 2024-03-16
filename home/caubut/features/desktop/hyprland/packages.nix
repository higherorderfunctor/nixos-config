{pkgs, ...}: {
  home = {
    packages = with pkgs;
    with gnome; [
      dconf # config backend for gnome # FIXME: not checked
      glib # gnome system libraries like gio
      (gnome-calculator.overrideAttrs
        (attrs: {
          buildInputs = attrs.buildInputs ++ [pkgs.glib-networking];
        }))
      gnome-calendar # calculator app
      gnome-font-viewer # font viewer # FIXME: check float
      nerdfonts # patched fonts with icons # FIXME: not checked
      wl-clipboard # copy/paste utility for wayland # FIXME: not checked
      xdg-utils # gnome utlities like xdg-open
    ];
  };

  # TODO: temp
  programs.kitty.enable = true;

  fonts.fontconfig.enable = true; # TODO: more options
}
# TODO: https://github.com/hyprwm/hyprpicker
