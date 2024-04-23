{inputs, ...}: (final: _: {
  inherit (inputs.nixpkgs-master.legacyPackages.${final.system}) spamassassin;
})
