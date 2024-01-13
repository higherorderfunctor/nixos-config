{
  home-manager,
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
  activation = {
    lazyVim = home-manager.lib.hm.dag.entryAfter ["writeBoundary"] ''
      $DRY_RUN_CMD nvim --headless "+Lazy! sync" +qa
    '';
  };
}
