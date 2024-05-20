{lib, ...}: final: prev: let
  nv = (import ./nvpkgs.nix).catppuccin-gtk;
  catppuccin-python-nv = (import ./nvpkgs.nix).catppuccin-python;
  # FIXME: https://github.com/catppuccin/gtk/issues/152
  # FIXME: https://github.com/NixOS/nixpkgs/issues/298043
  catppuccin-python =
    prev.python311Packages.catppuccin.overridePythonAttrs
    {
      inherit (catppuccin-python-nv) version;

      src = prev.fetchFromGitHub {
        inherit (catppuccin-python-nv.src) owner repo rev sha256;
      };

      # can be removed next version
      disabledTestPaths = [];
    };
in {
  # self: super: {
  #   catppuccin-gtk = args: super.catppuccin-gtk (args // {
  #     overrideAttrs = oldAttrs: rec {
  #       installPhase = ''
  #         echo "${args.variant}"
  #       '';
  #     };
  #   });
  # }
  catppuccin-gtk =
    prev.callPackage (
      args:
        (prev.catppuccin-gtk.override args).overrideAttrs (attrs: {
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

          patches = null;
          nativeBuildInputs =
            attrs.nativeBuildInputs
            ++ [
              final.git # for patches
            ];

          dontBuild = false;
          buildPhase = ''
            set -e
            python ./build.py ${args.variant} \
              -a all \
              --size ${args.size} \
              ${lib.optionalString (args.tweaks != []) "--tweaks " + builtins.toString args.tweaks} \
              --dest releases
          '';
          installPhase = ''
            set -e
            runHook preInstall

            mkdir -p $out/share
            cp -r releases $out/share/themes

            runHook postInstall
          '';
        })
    )
    # FIXME: cannot figure out how to use thse in a way to be overriden
    {
      # accents = ["sky"];
      # size = "compact";
      # tweaks = ["rimless" "black"];
      # variant = "mocha";
    };
}
#let
#     # FIXME: https://github.com/catppuccin/gtk/issues/145
#     patch-file = "colloid/src/sass/_colors.scss";
#     patch = ''
#       @function gtkmix($c1,$c2,$r) {
#         $ratio: 1 -  $r / 100%; // match SCSS mix()
#         @return unquote("mix(#{$c1},#{$c2},#{$ratio})");
#       }
#
#       @function gtkshade($c,$s) {
#         @return unquote("shade(#{$c},#{$s})");
#       }
#
#       @function gtkcolor($c) {
#         @return unquote("@#{$c}");
#       }
#     '';
#   in {
#     inherit (nv) version;
#     src = final.fetchFromGitHub {
#       inherit (nv.src) rev sha256;
#       owner = "catppuccin";
#       repo = "gtk";
#     };
#     buildInputs
#       final.gnome-themes-extra
#       catppuccin-python
#     ];
#     dontBuild = true;
#
#     prePatch = ''
#       cat <(echo '${patch}') ${patch-file} > ${patch-file}.patched
#       mv ${patch-file}.patched ${patch-file}
#     '';
#
#     buildPhase = ''
#       python ./build.py ${{ matrix.flavor }} -a all --zip -d $PWD/releases
#     '';
#
#     installPhase = ''
#       runHook preInstall
#
#       cp -r colloid colloid-base
#       mkdir -p $out/share/themes
#       export HOME=$(mktemp -d)
#
#       python3 install.py ${variant} \
#         ${lib.optionalString (accents != []) "--accent " + builtins.toString accents} \
#         ${lib.optionalString (size != []) "--size " + size} \
#         ${lib.optionalString (tweaks != []) "--tweaks " + builtins.toString tweaks} \
#         --dest $out/share/themes
#
#       runHook postInstall
#     '';
#
#     # FIXME: upstream patches break for catppuccin-python 1.x.x -> 2.xx
#     patches = [];
#   });
# }
