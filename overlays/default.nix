args: let
  import' = path: import path (args // {});
  overlays = [
    # ./amdvlk-overlay.nix
    ./arkenfox-overlay.nix
    ./astal-overlay.nix
    ./bruno-overlay.nix
    ./btop-overlay.nix
    ./bun-overlay.nix
    ./catppuccin-gtk-overlay.nix
    ./dns-root-hints-overlay.nix
    ./gitlab-language-server-overlay.nix
    ./fblog-overlay.nix
    ./firefox-nightly-overlay.nix
    ./gluetun-overlay.nix
    ./hotfixes-overlay.nix
    ./hyprland-overlay.nix
    ./mirrors-overlay.nix
    ./neovim-nightly-overlay.nix
    ./nix-gl-host-overlay.nix
    ./nixd-overlay.nix
    ./nvfetcher-overlay.nix
    ./oh-my-posh-overlay.nix
    ./otel-desktop-viewer-overlay.nix
    ./otel-tui-overlay.nix
    ./oxlint-overlay.nix
    ./pnpm-overlay.nix
    ./rust-overlay.nix
    ./spectral-overlay.nix
    ./standardnotes-overlay.nix
    ./tmux-which-key-overlay.nix
    # ./tree-sitter-cql-overlay.nix
    ./vivid-icons-themes-overlay.nix
    ./wezterm-overlay.nix
  ];
in
  map import' overlays
# TODO: add modules?
