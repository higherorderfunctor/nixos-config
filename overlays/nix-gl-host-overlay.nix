{inputs, ...}: (final: _: {
  nix-gl-host = inputs.nix-gl-host.defaultPackage.${final.system};
})
