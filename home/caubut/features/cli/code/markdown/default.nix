{pkgs, ...}: {
  home.packages = with pkgs; [
    # diagnostics
    nodePackages.alex
  ];
}
