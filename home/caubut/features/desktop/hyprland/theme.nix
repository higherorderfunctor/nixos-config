{pkgs, ...}: {
  home = {
    sessionVariables = {
      # disables the darkening of fonts around the stems
      FREETYPE_PROPERTIES = "cff:no-stem-darkening=0 autofitter:no-stem-darkening=0";
    };
    # cursor theme
    pointerCursor = {
      package = pkgs.catppuccin-cursors.mochaDark;
      name = "Catppuccin-Mocha-Dark-Cursors";
      size = 40;
      gtk.enable = true;
    };
  };

  # QT theme
  qt = {
    enable = true;
    platformTheme.name = "gtk3"; # follow GTK
  }; # TODO: other options?

  # GTK theme
  gtk = {
    enable = true;
    # font
    font = {
      name = "Ubuntu Nerd Font Regular";
    };
    # icon theme
    iconTheme = {
      name = "Vivid-Glassy-Dark-Icons";
      package = pkgs.vivid-icons-themes;
    };
    # decorations theme
    theme = {
      name = "Catppuccin-Macchiato-Compact-Sky-Dark";
      package =
        pkgs.catppuccin-gtk.override
        {
          accents = ["sky"];
          size = "compact";
          tweaks = ["rimless" "black"];
          variant = "macchiato";
        };
    };
  };
}
