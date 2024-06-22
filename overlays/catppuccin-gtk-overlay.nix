{lib, ...}: final: prev: let
  nv = (import ./nvpkgs.nix).catppuccin-gtk;
in {
  catppuccin-gtk =
    prev.callPackage (
      args:
        (prev.catppuccin-gtk.override args).overrideAttrs (attrs: {
          inherit (nv) version;

          # src = final.fetchFromGitHub {
          #   inherit (nv.src) rev sha256;
          #   owner = "catppuccin";
          #   repo = "gtk";
          # };

          src = builtins.fetchGit {
            inherit (nv.src) url rev;
            #hash = nv.src.sha256;
            submodules = true;
          };

          patches = null; # patches not needed for 1.x

          nativeBuildInputs =
            attrs.nativeBuildInputs
            ++ [
              final.git # to apply patches
            ];

          postUnpack = false; # use the submodule instead

          installPhase = ''
            set -e
            runHook preInstall

            python ./build.py ${args.variant} \
              ${lib.optionalString (args.accents != []) "--accent " + builtins.toString args.accents} \
              --size ${args.size} \
              ${lib.optionalString (args.tweaks != []) "--tweaks " + builtins.toString args.tweaks} \
              --dest releases

            mkdir -p $out/share
            cp -r releases $out/share/themes

            runHook postInstall
          '';
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
