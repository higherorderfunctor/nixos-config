_: final: prev: let
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
  #firefox = prev.firefox.overrideAttrs (_: {});
  firefox = prev.firefox.overrideAttrs (
    attrs:
      builtins.trace attrs attrs
  );
}
