{inputs, ...}: (final: _: {
  mcphub = inputs.mcphub.packages.${final.stdenv.hostPlatform.system}.default;
})
