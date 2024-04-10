{lib, ...}: (final: prev: let
  nv = (import ./nvpkgs.nix)."standardnotes-${final.system}";
in {
  bun = prev.bun.overrideAttrs {
    inherit (nv) version;
    passthru.sources = lib.mkForce {
      "${final.system}" = lib.fetchurl {
        inherit (nv.src) url sha256;
      };
    };
  };
})
