{pkgs, ...}: {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim;
    defaultEditor = true;
  };
}
