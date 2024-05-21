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
# #!/bin/bash
#
# base_dir="/path/to/your/folder"
#
# rename_and_symlink_directory() {
#     local dir="$1"
#     local base_name=$(basename "$dir")
#
#     local suffix=$(echo "$base_name" | grep -oE '(-[^-]+)?$')
#
#     local name_without_suffix=$(echo "$base_name" | sed -E 's/(\+.*)?(-[^-]+)?\/?$//' | awk -F- '{for(i=1;i<=NF;i++) if($i !~ /[^-]+$/) $i=toupper(substr($i,1,1)) substr($i,2)} 1' OFS=-)
#
#     local new_name="${name_without_suffix}${suffix}"
#
#     mv "$dir" "$(dirname "$dir")/$new_name"
#
#     ln -s "./$new_name" "$(dirname "$dir")/${name_without_suffix}-Dark${suffix}"
#     ln -s "./$new_name" "$(dirname "$dir")/${name_without_suffix}-Light${suffix}"
# }
#
# for dir in "$base_dir"/*/; do
#     # Check if it is a directory
#     if [ -d "$dir" ]; then
#         rename_and_symlink_directory "$dir"
#     fi
# done
