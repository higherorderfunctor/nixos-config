{inputs, ...}: {
  nix-update = inputs.nix-update.packages.${inputs.nixpkgs.system}.default;
}
