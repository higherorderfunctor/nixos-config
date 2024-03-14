{inputs, ...}: (final: _: {
  inherit
    (inputs.hyprland.packages.${final.system})
    hyprland
    xdg-desktop-portal-hyprland
    ;
})
