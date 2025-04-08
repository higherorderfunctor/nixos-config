{pkgs, ...}: {
  home.packages = with pkgs; [onlykey-cli gcr];
}
