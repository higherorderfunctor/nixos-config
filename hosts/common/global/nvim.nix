{
  inputs,
  pkgs,
  ...
}: {
  home.packages = [pkgs.mcphub];
  programs.neovim = {
    enable = true;
    package = pkgs.neovim;
    defaultEditor = true;
  };
}
