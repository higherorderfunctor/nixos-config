{inputs, ...}: [
  (import ./arkenfox-overlay.nix {inherit inputs;})
  (import ./btop-overlay.nix {inherit inputs;})
  (import ./catppuccin-gtk-overlay.nix {inherit inputs;})
  (import ./fblog-overlay.nix {inherit inputs;})
  (import ./firefox-nightly-overlay.nix {inherit inputs;})
  (import ./hyprbars-overlay.nix {inherit inputs;})
  (import ./hyprland-overlay.nix {inherit inputs;})
  (import ./neovim-nightly-overlay.nix {inherit inputs;})
  (import ./nix-gl-host-overlay.nix {inherit inputs;})
  (import ./nixd-overlay.nix {inherit inputs;})
  (import ./oh-my-posh.nix {inherit inputs;})
  (import ./spectral-overlay.nix {inherit inputs;})
  (import ./rust-overlay.nix {inherit inputs;})
  (import ./vivid-icons-themes-overlay.nix {inherit inputs;})
]
# TODO: add modules?
