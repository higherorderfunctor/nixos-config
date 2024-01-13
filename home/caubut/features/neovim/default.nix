{
  inputs,
  pkgs,
  ...
}: {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
  };
  home.file."./.config/nvim/" = {
    source = ./nvim-config;
    recursive = true;
  };
  home.activation = {
    lazyVim = inputs.home-manager.lib.hm.dag.entryAfter ["writeBoundary"] ''
      $DRY_RUN_CMD nvim --headless "+Lazy! restore" +qa
    '';
  };
}
