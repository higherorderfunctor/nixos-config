{pkgs, ...}: {
  home.packages = with pkgs; [oxlint oxc-language-server];
}
