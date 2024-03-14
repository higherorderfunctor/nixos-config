{inputs, ...}: (final: _: {
  inherit (inputs.hyprland-plugins.packages.${final.system}) hyprbars;
})
