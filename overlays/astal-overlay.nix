{inputs, ...}: final: _: {
  inherit (inputs.astal.packages.${final.stdenv.hostPlatform.system}) astal astalWithTypes;
}
