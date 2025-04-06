{inputs, ...}: final: _: {
  wezterm = inputs.wezterm.packages.${final.system}.default;
}
