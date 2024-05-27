args: let
  import' = path: import path (args // {});
  overlays = [
    ./arkenfox-overlay.nix
    ./astal-overlay.nix
    ./bruno-overlay.nix
    ./btop-overlay.nix
    ./bun-overlay.nix
    ./catppuccin-gtk-overlay.nix
    ./dns-root-hints-overlay.nix
    ./fblog-overlay.nix
    ./firefox-nightly-overlay.nix
    ./gluetun-overlay.nix
    ./hotfixes-overlay.nix
    ./hyprland-overlay.nix
    ./neovim-nightly-overlay.nix
    ./nix-gl-host-overlay.nix
    ./nvfetcher-overlay.nix
    ./nixd-overlay.nix
    ./oh-my-posh-overlay.nix
    ./spectral-overlay.nix
    ./standardnotes-overlay.nix
    ./rust-overlay.nix
    # ./tree-sitter-cql-overlay.nix
    ./vivid-icons-themes-overlay.nix
  ];
in
  map import' overlays
# TODO: add modules?
