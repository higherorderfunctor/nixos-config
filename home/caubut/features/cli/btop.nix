{
  lib,
  pkgs,
  ...
}: let
  catppuccin-btop = pkgs.stdenv.mkDerivation {
    name = "catppuccin-btop";

    src = pkgs.fetchFromGitHub {
      owner = "catppuccin";
      repo = "btop";
      rev = "c6469190f2ecf25f017d6120bf4e050e6b1d17af";
      sha256 = "sha256-jodJl4f2T9ViNqsY9fk8IV62CrpC5hy7WK3aRpu70Cs=";
    };

    dontConfigure = true;
    dontBuild = true;

    installPhase = ''
      ls
      mv themes "$out"
    '';
  };
in {
  programs.btop = {
    enable = true;
    package = pkgs.btop;
    settings = {
      color_theme = "catppuccin_mocha";
      theme_background = false;
      clock_format = "%a, %b %m %Y %I:%M %p";
    };
  };
  xdg.configFile."btop/themes" = {
    source = catppuccin-btop;
    recursive = true;
  };
}
# TODO: https://github.com/catppuccin/btop
