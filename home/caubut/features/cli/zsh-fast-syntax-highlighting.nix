{
  config,
  lib,
  pkgs,
  ...
}: let
  configDir = "zsh/plugins/zsh-fast-syntax-highlighting";
  zsh-fast-syntax-highlighting = pkgs.stdenvNoCC.mkDerivation rec {
    name = "zsh-fast-syntax-highlighting";

    srcs = [
      (builtins.fetchTarball {
        url = "https://github.com/zdharma-continuum/fast-syntax-highlighting/archive/master.tar.gz";
        # sha256 = lib.fakeSha256;
        sha256 = "1bmrb724vphw7y2gwn63rfssz3i8lp75ndjvlk5ns1g35ijzsma5";
        name = "fast-syntax-highlighting";
      })
      (
        builtins.fetchTarball {
          url = "https://github.com/catppuccin/zsh-fsh/archive/master.tar.gz";
          # sha256 = lib.fakeSha256;
          sha256 = "1044pbfykcm16m7v3vwc6g1f9r3cxxmlaqch670yw6appbw62nfz";
          name = "fast-syntax-highlighting-catppuccin";
        }
      )
    ];

    sourceRoot = name;

    strictDeps = true;
    dontConfigure = true;
    dontBuild = true;
    unpackPhase = ''
      printf '%s\n' "''${srcs[@]}"
      echo ""''${srcs[0]}""
      echo ""''${srcs[1]}""
      cp "''${srcs[0]}" $(stripHash "''${srcs[0]}")
      cp "''${srcs[1]}" $(stripHash "''${srcs[0]}")/plugins/zsh-fast-syntax-highlighting/themes
    '';
    # unpackPhase = ''
    #   cp ''${srcs[0]}/* "$out"
    #   cp ''${srcs[1]}/* "$out/plugins/zsh-fast-syntax-highlighting/themes"
    # '';

    # installPhase = ''
    #   cp ''${srcs[0]}/* "$out"
    #   cp ''${srcs[1]}/* "$out/plugins/zsh-fast-syntax-highlighting/themes"
    # '';
  };
in {
  programs.zsh.initExtra = ''
    # fast-syntax-highlighting
    source "${config.xdg.configHome}/${configDir}/fast-syntax-highlighting.plugin.zsh"
  '';
  xdg.configFile."${configDir}" = {
    source = zsh-fast-syntax-highlighting;
    recursive = true;
  };
}
