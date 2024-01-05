{
  config,
  pkgs,
  ...
}: {
  xdg.enable = true;
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    coc.enable = false;
  };
  xdg.configFile."nvim"


  # home.file."./nixos-config/" = {
  #   source = ../../../../..;
  #   recursive = true;
  # };

  # home.file."./.config/nvim/".source = config.lib.file.mkOutOfStoreSymlink "nixos-config/home/caubut/features/neovim/nvim-config";
}
# NOTES":
#   new ssh key for secrets
#     copy to new persisted location
#   remove /etc/nixos
#   nvim-config submodule??
#     usable on other systems
#     use the source to keep synced with store
#
#   updates require updating submodule
#     rebuild to be there next boot
#
#   or just keep one repo and symlink...
