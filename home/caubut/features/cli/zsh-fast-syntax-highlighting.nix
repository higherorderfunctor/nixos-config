
{
  config,
  lib,
  pkgs,
  ...
}: let
  configDir = "zsh/plugins/zsh-fast-syntax-highlighting";
  sources = {
    fast-syntax-highlighting = builtins.fetchTarball {
      url = "https://github.com/zdharma-continuum/fast-syntax-highlighting/archive/master.tar.gz";
      # sha256 = lib.fakeSha256;
      sha256 = "1bmrb724vphw7y2gwn63rfssz3i8lp75ndjvlk5ns1g35ijzsma5";
      name = "fast-syntax-highlighting";
    };
    fast-syntax-highlighting-catppuccin = builtins.fetchTarball {
      url = "https://github.com/catppuccin/zsh-fsh/archive/master.tar.gz";
      # sha256 = lib.fakeSha256;
      sha256 = "1044pbfykcm16m7v3vwc6g1f9r3cxxmlaqch670yw6appbw62nfz";
      name = "fast-syntax-highlighting-catppuccin";
    };
  };
  zsh-fast-syntax-highlighting = pkgs.stdenvNoCC.mkDerivation rec {
    name = "zsh-fast-syntax-highlighting";

    srcs = lib.attrValues sources;

    strictDeps = true;
    dontConfigure = true;
    dontBuild = true;
    unpackPhase = ''
      IFS=' ' read -r -a src <<< "$srcs"
      printf '%s\n' "''${src[@]}"
      echo ""''${src[0]}""
      echo ""''${src[1]}""
      ls -la
      cp -r "''${src[0]}" $(stripHash "''${src[0]}")
      ls -la
      chmod u+w $(stripHash "''${src[0]}")/themes
      ls -la
      cp -r "''${src[1]}"/themes/* $(stripHash "''${src[0]}")/themes
      ls -la
      chmod u-w $(stripHash "''${src[0]}")/themes
      ls -la
    '';
    # unpackPhase = ''
    #   cp ''${srcs[0]}/* "$out"
    #   cp ''${srcs[1]}/* "$out/plugins/zsh-fast-syntax-highlighting/themes"
    # '';

    installPhase = ''
      ls -la
      cp -r fast-syntax-highlighting "$out"
    '';
  };
in {
  programs.zsh.initExtra = ''
    # fast-syntax-highlighting
    source "${config.xdg.configHome}/${configDir}/fast-syntax-highlighting.plugin.zsh"
    if ! fast-theme --show | grep -q 'catppuccin-mocha'; then
      fast-theme catppuccin-mocha
    fi
  '';
  xdg.configFile."${configDir}" = {
    source = zsh-fast-syntax-highlighting;
    recursive = true;
  };
}
