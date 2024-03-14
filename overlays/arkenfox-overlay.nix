_: final: _: let
  nv = (import ./nvpkgs.nix).arkenfox;
  arkenfox = final.stdenvNoCC.mkDerivation {
    inherit (nv) version;
    pname = nv.name;
    src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
    installPhase = ''
      mv user.js "$out"
    '';
  };
in {
  inherit arkenfox;
}
