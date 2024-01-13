{
  config,
  inputs,
  pkgs,
  ...
}: {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    extraPackages = with pkgs; [
      gcc
    ];
  };
  home.file."./.config/nvim/" = {
    source = ./nvim-config;
    recursive = true;
  };
  home.activation = {
    nvim = inputs.home-manager.lib.hm.dag.entryAfter ["installPackages"] ''
      PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD nvim --headless "+Lazy! restore" +qa
    '';
  };
}
