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
# TODO:
# _: let
#   nv = (import ./nvpkgs.nix).oh-my-posh;
# in
#   final: prev: let
#     inherit (final) lib;
#   in {
#     oh-my-posh = prev.oh-my-posh.overrideAttrs (orig: let
#       replaceVersion = flag:
#         if lib.strings.hasInfix "build.Version" flag
#         then
#           lib.strings.concatStringsSep "=" [
#             (builtins.head (lib.splitString "=" flag))
#             nv.version
#           ]
#         else flag;
#     in {
#       inherit (nv) version;
#       src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
#       vendorHash = "sha256-WuPEoDmp/SSf3AqHtYTtMb56PnjZLWr3weZQXEF7pbg=";
#       ldflags = builtins.map replaceVersion orig.ldflags;
#       # postPatch =
#       #   orig.postPatch
#       #   + ''
#       #     rm engine/image_test.go \
#       #        engine/migrate_glyphs_test.go \
#       #        segments/nba_test.go
#       #   '';
#     });
#   }
