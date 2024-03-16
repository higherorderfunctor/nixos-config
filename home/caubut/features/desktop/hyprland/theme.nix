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
    platformTheme = "gtk3"; # follow GTK
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
        (pkgs.catppuccin-gtk.override
          {
            accents = ["sky"];
            size = "compact";
            tweaks = ["rimless" "black"];
            variant = "macchiato";
          })
        .overrideAttrs (_: let
          # FIXME: https://github.com/catppuccin/gtk/issues/145
          patch-file = "colloid/src/sass/_colors.scss";
          patch = ''
            @function gtkmix($c1,$c2,$r) {
              $ratio: 1 -  $r / 100%; // match SCSS mix()
              @return unquote("mix(#{$c1},#{$c2},#{$ratio})");
            }

            @function gtkshade($c,$s) {
              @return unquote("shade(#{$c},#{$s})");
            }

            @function gtkcolor($c) {
              @return unquote("@#{$c}");
            }
          '';
        in {
          # TODO: remove debug
          prePatch = ''
            cat ${patch-file}
            cat <(echo '${patch}') ${patch-file} > ${patch-file}.patched
            cat ${patch-file}.patched
            echo '${patch}'
            echo '${patch-file}'
            echo '${patch-file}.patched'
            mv ${patch-file}.patched ${patch-file}
          '';
        });
    };
  };
}
