{pkgs, ...}: {
  # calendar app
  home.packages = [
    ( # calculator app
      pkgs.gnome-calculator.overrideAttrs
      (attrs: {
        # patches currency lookups
        buildInputs = attrs.buildInputs ++ [pkgs.glib-networking];
      })
    )
  ];
}
