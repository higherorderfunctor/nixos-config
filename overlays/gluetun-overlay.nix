_: final: prev: let
  inherit (final) lib;
  nv = (import ./nvpkgs.nix).gluetun-src;
  dropFirstChar = s: builtins.substring 1 (builtins.stringLength s) s;
  version = dropFirstChar nv.version;
  # replaceVersion = flag:
  #   if lib.strings.hasInfix "build.Version" flag
  #   then
  #     lib.strings.concatStringsSep "=" [
  #       (builtins.head (lib.splitString "=" flag))
  #       version
  #     ]
  #   else flag;
  # src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  vendorHash =
    if lib.hasAttr "vendorHash" nv
    then nv.vendorHash
    else "sha256-Xus59zWfxxdamcTL2Q3vLGIrChmr2Dix9/cRB+enwt0="; # FIXME: lib.fakeHash;
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
    pname = "gluetun";
    inherit version;

    src = final.fetchFromGitHub {
      inherit (nv.src) owner repo rev sha256;
    };

    inherit vendorHash;

    postPatch = ''
      rm internal/tun/tun_test.go
    '';

    meta = with lib; {
      description =
        "VPN client in a thin Docker container for multiple VPN providers, written in Go, and using OpenVPN or "
        + "Wireguard, DNS over TLS, with a few proxy servers built-in. ";
      mainProgram = "gluetun";
      homepage = "https://github.com/qdm12/gluetun";
      license = licenses.mit;
      maintainers = with maintainers; [qdm12];
    };
  };
}
