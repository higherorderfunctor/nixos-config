_: final: _: let
  nv = (import ./nvpkgs.nix).dns-root-hints;
in {
  dns-root-hints = final.stdenvNoCC.mkDerivation {
    pname = nv.name;
    inherit (nv) version;
    src = final.fetchurl {inherit (nv.src) url sha256;};
    phases = ["installPhase"];
    installPhase = ''
      mkdir -p "$out"
      cp "$src" "$out/root.hints"
    '';
  };
}
