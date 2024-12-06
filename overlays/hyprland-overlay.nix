{
  inputs,
  lib,
  ...
}:
lib.composeManyExtensions (
  # (lib.attrValues inputs.hyprland.overlays)
  ##++ [
  [
    inputs.hyprland.overlays.default
    inputs.hypridle.overlays.default
    inputs.hyprland-plugins.overlays.default
    inputs.hyprlock.overlays.default
    inputs.hyprpicker.overlays.default
    (final: _: let
      catppuccin-hyprland-nv = (import ./nvpkgs.nix).catppuccin-hyprland;
      catppuccin-hyprlock-nv = (import ./nvpkgs.nix).catppuccin-hyprlock;
    in {
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
  ]
)
