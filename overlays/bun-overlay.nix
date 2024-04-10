_: (final: prev: let
  nv = (import ./nvpkgs.nix)."bun-${final.system}";
  version = "${nv.version}-1";
in {
  bun = prev.bun.overrideAttrs {
    inherit version;
    src = final.fetchurl {
      inherit (nv.src) url sha256;
    };
  };
})
