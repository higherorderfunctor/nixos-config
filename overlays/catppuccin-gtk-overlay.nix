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
          buildPhase = ''
            set -e
            python ./build.py ${args.variant} \
              ${lib.optionalString (args.accents != []) "--accent " + builtins.toString args.accents} \
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
    {};
}
