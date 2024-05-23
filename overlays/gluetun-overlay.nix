_: final: prev: let
  inherit (final) lib;
  nv = (import ./nvpkgs.nix).gluetun-src;
  # dropFirstChar = s: builtins.substring 1 (builtins.stringLength s) s;
  # replaceVersion = flag:
  #   if lib.strings.hasInfix "build.Version" flag
  #   then
  #     lib.strings.concatStringsSep "=" [
  #       (builtins.head (lib.splitString "=" flag))
  #       version
  #     ]
  #   else flag;
  # version = dropFirstChar nv.version;
  # src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  # vendorHash =
  #   if lib.hasAttr "vendorHash" nv
  #   then nv.vendorHash
  #   else lib.fakeHash;
  buildGoModule = let
    nv = (import ./nvpkgs.nix).go;
    go = final.go.overrideAttrs {
      inherit (nv) version;
      src = final.fetchurl {
        inherit (nv.src) url sha256;
      };
    };
  in
    final.buildGoModule.override {inherit go;};
in {
  gluetun = buildGoModule {
    inherit (nv) version;
    src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  };
}
