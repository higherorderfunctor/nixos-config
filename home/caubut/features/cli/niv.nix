{pkgs, ...}: {
  home.packages = [pkgs.niv pkgs.nvfetcher];
}
