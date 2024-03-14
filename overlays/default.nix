{inputs, ...}: [
  (import ./firefox-nightly-overlay.nix {inherit inputs;})
  (import ./hyprbars-overlay.nix {inherit inputs;})
  (import ./hyprland-overlay.nix {inherit inputs;})
  (import ./neovim-nightly-overlay.nix {inherit inputs;})
  (import ./nix-gl-host-overlay.nix {inherit inputs;})
  (import ./nixd-overlay.nix {inherit inputs;})
  (import ./nixd-overlay.nix {inherit inputs;})
  (import ./oh-my-posh.nix {inherit inputs;})
  (import ./rust-overlay.nix {inherit inputs;})
  (import ./vivid-icons-themes-overlay.nix {inherit inputs;})
]
# TODO: add modules?
