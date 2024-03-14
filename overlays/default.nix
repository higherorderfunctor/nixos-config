{inputs}: let
  nix-update-overlay = import ./nix-update-overlay.nix {inherit inputs;};
in [
  nix-update-overlay
  neovim-nightly-overlay.overlays.default
  nixd.overlays.default
  rust-overlay.overlays.default
  (_: _: {firefox-nightly = inputs.firefox-nightly.packages.${inputs.nixpkgs.system}.firefox-nightly-bin;})
  (_: _: {
    inherit (hyprland-plugins.packages.${inputs.nixpkgs.system}) hyprbars;
  })
  (_: _: {nix-gl-host = nix-gl-host.defaultPackage.${inputs.nixpkgs.system};})
  (_: _: {nix-update = nix-update.packages.${inputs.nixpkgs.system}.default;})
  (_: super: {
    vivid-icons-themes = super.callPackage ./modules/nixos/vivid-icons-themes.nix {};
  })
]
