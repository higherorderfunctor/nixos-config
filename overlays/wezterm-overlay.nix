_: let
  nv = (import ./nvpkgs.nix).wezterm;
in
  final: prev: let
    inherit (final) lib;
    rustPlatform = final.makeRustPlatform {
      cargo = final.rust-bin.stable.latest.default;
      rustc = final.rust-bin.stable.latest.default;
    };
  in {
    wezterm =
      prev.wezterm.override
      (_: {
        rustPlatform.buildRustPackage = args:
          rustPlatform.buildRustPackage (args
            // {
              inherit (nv) version;
              src = final.fetchgit {
                inherit (nv.src) url rev fetchSubmodules deepClone leaveDotGit sparseCheckout sha256;
              };
              cargoLock = {
                lockFile = ./.nvfetcher/${lib.head nv.cargoLocks."Cargo.lock"};
                allowBuiltinFetchGit = true;
              };
              cargoHash = null;
            });
      });
    }
