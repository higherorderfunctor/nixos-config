{inputs, ...}: (final: _: {
  mcp-hub = inputs.mcp-hub.packages.${final.stdenv.hostPlatform.system}.default;
})
