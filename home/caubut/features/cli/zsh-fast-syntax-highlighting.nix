{
  config,
  lib,
  pkgs,
  ...
}: let
  configDir = "zsh/plugins/fast-syntax-highlighting";
  sources = {
    fast-syntax-highlighting = builtins.fetchTarball {
      url = "https://github.com/zdharma-continuum/fast-syntax-highlighting/archive/master.tar.gz";
      # sha256 = lib.fakeSha256;
      sha256 = "1bmrb724vphw7y2gwn63rfssz3i8lp75ndjvlk5ns1g35ijzsma5";
    };
    fast-syntax-highlighting-catppuccin = builtins.fetchTarball {
      url = "https://github.com/catppuccin/zsh-fsh/archive/master.tar.gz";
      # sha256 = lib.fakeSha256;
      sha256 = "1044pbfykcm16m7v3vwc6g1f9r3cxxmlaqch670yw6appbw62nfz";
    };
  };
  fast-syntax-highlighting = pkgs.stdenvNoCC.mkDerivation {
    name = "zsh-fast-syntax-highlighting-catppuccin";

    srcs = lib.attrValues sources;

    strictDeps = true;
    dontConfigure = true;
    dontBuild = true;

    unpackPhase = ''
      cp ''${srcs[0]}/* "$out"
      cp ''${srcs[1]}/* "$out/plugins/fast-syntax-highlighting/themes"
    '';
  };
in {
  programs.zsh.initExtra = ''
    # fast-syntax-highlighting
    source "${config.xdg.configHome}/${configDir}/fast-syntax-highlighting.plugin.zsh"
  '';
  xdg.configFile."${configDir}" = {
    source = fast-syntax-highlighting;
    recursive = true;
  };
}