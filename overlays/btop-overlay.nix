_: final: prev: let
  nv = (import ./nvpkgs.nix).btop;
  catppuccin-nv = (import ./nvpkgs.nix).catppuccin-btop;
  catppuccin-btop = final.stdenv.mkDerivation {
    inherit (nv) version;
    pname = catppuccin-nv.name;
    src = final.fetchFromGitHub {inherit (catppuccin-nv.src) owner repo rev sha256;};
    dontConfigure = true;
    dontBuild = true;
    installPhase = ''
      ls
      mv themes "$out"
    '';
  };
in {
  inherit catppuccin-btop;
  btop = prev.btop.overrideAttrs (_: {
    inherit (nv) version;
    src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  });
}
