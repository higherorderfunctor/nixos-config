_: (final: _: let
  nv = (import ./nvpkgs.nix).arkenfox;
  src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  arkenfox = final.lib.readFile "${src}/user.js";
in {
  inherit arkenfox;
})
