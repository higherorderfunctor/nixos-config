# _: {
#   _,
#   prev,
# }: {
#   kiro-cli =
#     prev.kiro-cli.overrideAttrs
#     (old: {
#       src = old.src.overrideAttrs (_: {
#         hash = "sha256-aB8snKmASQM9lOuyyvsqlF5TuJ7nFLd6OlUvfj25G9Q="; # final.lib.fakeHash;
#       });
#     });
# }
_: (final: prev: let
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    ."kiro-cli";
in {
  kiro-cli = prev.kiro-cli.overrideAttrs {
    inherit (nv) src version;

    meta =
      prev.kiro-cli.meta
      // {
        changelog = builtins.replaceStrings [prev.kiro-cli.version] [nv.version] prev.kiro-cli.meta.changelog;
      };
  };
})
