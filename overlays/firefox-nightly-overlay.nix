{inputs, ...}: (final: _: {
  firefox-nightly = inputs.firefox-nightly.packages.${final.system}.firefox-nightly-bin;
})
