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
        rustPlatform.buildRustPackage (args
          // {
            pname = "oxlint";
            inherit (nv) version src;
            cargoLock = nv.cargoLock."Cargo.lock";
            buildInputs =
              args.buildInputs
              ++ [
                final.nodejs
              ];
          });
    });
  oxc-language-server =
    (prev
      .oxlint
      .overrideAttrs {
        meta = mkMeta {
          homepage = "https://github.com/oxc-project/oxc/tree/main/crates/oxc_language_server";
          mainProgram = "oxc-language-server";
        };
      })
    .override
    (_: {
      rustPlatform.buildRustPackage = args:
        rustPlatform.buildRustPackage (args
          // rec {
            pname = "oxc-language-server";
            inherit (nv) version src;
            cargoLock = nv.cargoLock."Cargo.lock";
            buildInputs =
              args.buildInputs
              ++ [
                final.nodejs
              ];
            cargoWorkspaceDir = "${nv.src}/crates/oxc_language_server";
            cargoBuildFlags = ["--bin=oxc_language_server"];
            cargoTestFlags = cargoBuildFlags;
          });
    });
in {
  inherit oxlint oxc-language-server;
}
