{inputs, ...}: (final: _: {
  nix-update = inputs.nix-update.packages.${final.system}.default;
})
