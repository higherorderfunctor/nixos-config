_: final: prev: let
  inherit (final) lib;
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    .oxc;
  rustPlatform = final.makeRustPlatform {
    cargo = final.rust-bin.stable.latest.default;
    rustc = final.rust-bin.stable.latest.default;
  };
  mkMeta = {
    mainProgram,
    homepage,
  }:
    with lib; {
      inherit mainProgram homepage;
      description = "Suite of high-performance tools for JavaScript and TypeScript written in Rust";
      changelog = "https://github.com/oxc-project/oxc/releases/tag/oxlint_v${nv.version}";
      license = licenses.mit;
      maintainers = with maintainers; [oxc-project];
    };
  oxlint =
    (prev
      .oxlint
      .overrideAttrs {
      meta = mkMeta {
        homepage = "https://github.com/oxc-project/oxc/tree/main/apps/oxlint";
        mainProgram = "oxlint";
      };
    })
    .override
    (_: {
      rustPlatform.buildRustPackage = args:
        rustPlatform.buildRustPackage (
          finalAttrs: let
            a = (lib.toFunction args) finalAttrs;
          in
            a
            // {
              pname = "oxlint";
              inherit (nv) version src;
              cargoLock = nv.cargoLock."Cargo.lock";
              buildInputs = (a.buildInputs or []) ++ [final.nodejs];
            }
        );
    });
in {
  inherit oxlint;
}
