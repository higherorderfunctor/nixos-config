{pkgs, ...}: {
  home.packages = with pkgs; [networkmanager];
}
