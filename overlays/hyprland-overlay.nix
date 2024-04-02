{inputs, ...}: (final: _: let
  catppuccin-hyprland-nv = (import ./nvpkgs.nix).catppuccin-hyprland;
  catppuccin-hyprlock-nv = (import ./nvpkgs.nix).catppuccin-hyprlock;
in {
  inherit
    (inputs.hyprland.packages.${final.system})
    hyprland
    xdg-desktop-portal-hyprland
    ;
  inherit (inputs.hypridle.packages.${final.system}) hypridle;
  inherit (inputs.hyprland-plugins.packages.${final.system}) hyprbars;
  inherit (inputs.hyprlock.packages.${final.system}) hyprlock;

  catppuccin-hyprland = final.stdenvNoCC.mkDerivation {
    inherit (catppuccin-hyprland-nv) version;
    pname = catppuccin-hyprland-nv.name;
    src = final.fetchFromGitHub {
      inherit (catppuccin-hyprland-nv.src) rev sha256;
      owner = "catppuccin";
      repo = "hyprland";
    };
    installPhase = ''
      mv themes "$out"
    '';
  };

  catppuccin-hyprlock = final.stdenvNoCC.mkDerivation {
    inherit (catppuccin-hyprlock-nv) version;
    pname = catppuccin-hyprlock-nv.name;
    src = final.fetchFromGitHub {
      inherit (catppuccin-hyprlock-nv.src) rev sha256;
      owner = "catppuccin";
      repo = "hyprlock";
    };
    installPhase = ''
      mkdir $out
      mv hyprlock.conf "$out/hyprlock.conf"
    '';
  };
})
# FIXME: use official overlays
