{lib, ...}: final: prev: let
  nv = (import ./nvpkgs.nix).catppuccin-gtk;
in {
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

          patches = null;
          nativeBuildInputs =
            attrs.nativeBuildInputs
            ++ [
              final.git # to apply patches
            ];

          dontBuild = false;

          preInstall = ''
            set -e
            python ./build.py ${args.variant} \
              ${lib.optionalString (args.accents != []) "--accent " + builtins.toString args.accents} \
              --size ${args.size} \
              ${lib.optionalString (args.tweaks != []) "--tweaks " + builtins.toString (args.tweaks ++ ["oled"])} \
              --dest releases
          '';

          installPhase = ''
            set -e
            runHook preInstall

            mkdir -p $out/share
            cp -r releases $out/share/themes

            runHook postInstall
          '';

          fixupPhase = "true";
        })
    )
    {};
}
# mkdir -p $out/share/themes
# # cp -r releases $out/share/themes
# cd releases
# for dir in "$base_dir"/*/; do
#   if [ -d "$dir" ]; then
#     IFS=-
#     tokens=( $input )
#     read -a tokens <<< "''${tokens[*]^}";
#     filename="$(echo "''${name[*]%%+*}")"
#     IFS=$originalIFS
#     mv "$dir" "$out/share/themes/$filename"
#   fi
# done
