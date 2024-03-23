_: final: prev: let
  nv = (import ./nvpkgs.nix).catppuccin-gtk;
  # FIXME: https://github.com/catppuccin/gtk/issues/152
  # FIXME: https://github.com/NixOS/nixpkgs/issues/298043
  catppuccin-python =
    prev.python311Packages.catppuccin.overridePythonAttrs
    (_: rec {
      version = "1.3.2";

      src = prev.fetchFromGitHub {
        owner = "catppuccin";
        repo = "python";
        rev = "refs/tags/v${version}";
        hash = "sha256-spPZdQ+x3isyeBXZ/J2QE6zNhyHRfyRQGiHreuXzzik=";
      };

      # can be removed next version
      disabledTestPaths = [
        "tests/test_flavour.py" # would download a json to check correctness of flavours
      ];
    });
in {
  catppuccin-gtk = prev.catppuccin-gtk.overrideAttrs (_: let
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
    inherit (nv) version;
    src = final.fetchFromGitHub {
      inherit (nv.src) rev sha256;
      owner = "catppuccin";
      repo = "gtk";
    };
    buildInputs = [
      final.gnome-themes-extra
      catppuccin-python
    ];
    prePatch = ''
      cat <(echo '${patch}') ${patch-file} > ${patch-file}.patched
      mv ${patch-file}.patched ${patch-file}
    '';
  });
}
