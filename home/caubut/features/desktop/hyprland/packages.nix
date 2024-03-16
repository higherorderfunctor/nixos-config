{pkgs, ...}: {
  home = {
    packages = with pkgs;
    with gnome; [
      # dconf
      # glib # gnome system libraries like gio
      # ( # calculator app
      #   gnome-calculator.overrideAttrs
      #   (attrs: {
      #     # patches currency lookups
      #     buildInputs = attrs.buildInputs ++ [pkgs.glib-networking];
      #   })
      # )
      # gnome-calendar # calculator app
      # gnome-font-viewer # font viewer # FIXME: # TODO: float
      # nerdfonts # patched fonts with icons # FIXME: not checked
      # wl-clipboard # copy/paste utility for wayland # FIXME: not checked
      # xdg-utils # gnome utlities like xdg-open
    ];
  };

  # TODO: temp
  programs.kitty.enable = true;

  fonts.fontconfig.enable = true; # TODO: more options
}
# TODO: https://github.com/hyprwm/hyprpicker
