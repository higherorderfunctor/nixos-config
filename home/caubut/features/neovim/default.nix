{
  config,
  pkgs,
  ...
}: {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    coc.enable = false;
  };
  xdg.configFile."nvim".source = config.lib.file.mkOutOfStoreSymlink "/home/${config.home.username}/Documents/nixos-config/home/caubut/features/neovim/nvim-config";

  # home.file."./nixos-config/" = {
  #   source = ../../../../..;
  #   recursive = true;
  # };

  # home.file."./.config/nvim/".source = config.lib.file.mkOutOfStoreSymlink "nixos-config/home/caubut/features/neovim/nvim-config";
}
# NOTES":
#   or just keep one repo and symlink...
