_: (final: prev: let
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    .pnpm;
in {
  pnpm = prev.pnpm.overrideAttrs {
    inherit (nv) src version;

    meta =
      prev.pnpm.meta
      // {
        changelog = builtins.replaceStrings [prev.pnpm.version] [nv.version] prev.pnpm.meta.changelog;
      };
  };
})
