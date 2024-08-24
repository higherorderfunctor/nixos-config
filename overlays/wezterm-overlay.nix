_: final: prev: let
  rustPlatform = final.makeRustPlatform {
    cargo = final.rust-bin.stable.latest.default;
    rustc = final.rust-bin.stable.latest.default;
  };
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    .wezterm;
in {
  wezterm =
    prev.wezterm.override
    (_: {
      rustPlatform.buildRustPackage = args: (rustPlatform.buildRustPackage (args
        // {
          inherit (nv) pname version src date;
          cargoLock = nv.cargoLock."Cargo.lock";
          cargoHash = null;
        }));
    });
}
