_: final: prev: let
  inherit (final) lib;
  nv = (import ./nvpkgs.nix).gh;
  dropFirstChar = s: builtins.substring 1 (builtins.stringLength s) s;
  version = dropFirstChar nv.version;

  vendorHash =
    if lib.hasAttr "vendorHash" nv
    then nv.vendorHash
    else lib.fakeHash;
in {
  gh = prev.gh.overrideAttrs (_: {
    inherit version vendorHash;
    src = final.fetchFromGitHub {
      inherit (nv.src) owner repo rev sha256;
    };
  });
}
