{inputs, ...}: final: _: {
  inherit (inputs.astal.packages.${final.system}) astal astalWithTypes;
}
