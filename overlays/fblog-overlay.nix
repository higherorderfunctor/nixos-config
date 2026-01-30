_: let
  nv = (import ./nvpkgs.nix).fblog;
in
  final: prev: let
    inherit (final) lib;

    version = lib.removePrefix "v" nv.version;

    rustPlatform = final.makeRustPlatform {
      cargo = final.rust-bin.stable.latest.default;
      rustc = final.rust-bin.stable.latest.default;
    };
  in {
    fblog = prev.fblog.override (_: {
      rustPlatform.buildRustPackage = args:
        rustPlatform.buildRustPackage (finalAttrs: let
          a = (lib.toFunction args) finalAttrs;
        in
          a
          // {
            pname = nv.name;
            inherit version;

            src = final.fetchFromGitHub {
              inherit (nv.src) owner repo rev sha256; # rev can stay "v4.17.0"
            };

            cargoLock = {
              lockFile = ./.nvfetcher/${lib.head nv.cargoLock."Cargo.lock"};
              allowBuiltinFetchGit = true;
            };

            cargoHash = null;
          });
    });
  }
