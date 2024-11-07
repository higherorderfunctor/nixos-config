_: final: prev: let
  nv = (import ./nvpkgs.nix).btop;
  dropFirstChar = s: builtins.substring 1 (builtins.stringLength s) s;
  version = dropFirstChar nv.version;
  catppuccin-btop-nv = (import ./nvpkgs.nix).catppuccin-btop;
  catppuccin-btop = final.stdenv.mkDerivation {
    inherit (catppuccin-btop-nv) version;
    pname = catppuccin-btop-nv.name;
    src = final.fetchFromGitHub {inherit (catppuccin-btop-nv.src) owner repo rev sha256;};
    dontConfigure = true;
    dontBuild = true;
    installPhase = ''
      mv themes "$out"
    '';
  };
in {
  inherit catppuccin-btop;
  btop = prev.btop.overrideAttrs (_: {
    inherit version;
    src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  });
}
