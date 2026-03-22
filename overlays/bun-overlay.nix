_: (final: prev: let
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    ."bun-${final.stdenv.hostPlatform.system}";
in {
  bun = prev.bun.overrideAttrs {
    inherit (nv) src version;

    meta =
      prev.bun.meta
      // {
        changelog = builtins.replaceStrings [prev.bun.version] [nv.version] prev.bun.meta.changelog;
      };
  };
})
