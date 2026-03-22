{inputs, ...}: final: _: {
  wezterm = inputs.wezterm.packages.${final.stdenv.hostPlatform.system}.default;
}
