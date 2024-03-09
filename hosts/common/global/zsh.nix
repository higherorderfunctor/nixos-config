{pkgs, ...}: {
  programs.zsh = {
    enable = true;
    package = pkgs.zsh;
    enableCompletion = false;
  };
}
