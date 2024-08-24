_: final: prev: let
  inherit (final) lib;
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
          # {
          #   inherit (nv.cargoLock."Cargo.lock") lockFile outputHashes;
          #   allowBuiltinFetchGit = true;
          # };
          postPatch =
            builtins.concatStringsSep
            "\n"
            (["cp ${nv.cargoLock."Cargo.lock".lockFile} Cargo.lock"]
              ++ (builtins.tail (lib.splitString "\n" args.postPatch)));
          cargoHash = null;
        }));
    });
}
