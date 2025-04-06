_: let
  nv = (import ./nvpkgs.nix).fblog;
in
  final: prev: let
    inherit (final) lib;
    rustPlatform = final.makeRustPlatform {
      cargo = final.rust-bin.stable.latest.default;
      rustc = final.rust-bin.stable.latest.default;
    };
  in {
    fblog =
      prev.fblog.override
      (_: {
        rustPlatform.buildRustPackage = args:
          rustPlatform.buildRustPackage (args
            // {
              inherit (nv) version;
              pname = nv.name;
              src = final.fetchFromGitHub {
                inherit (nv.src) owner repo rev sha256;
              };
              cargoLock = {
                lockFile = ./.nvfetcher/${lib.head nv.cargoLocks."Cargo.lock"};
                allowBuiltinFetchGit = true;
              };
              cargoHash = null;
            });
      });
  }
