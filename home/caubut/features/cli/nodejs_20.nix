{pkgs, ...}: {
  home.packages = with pkgs; [
    nodejs_20
    nodePackages.yarn
    nodePackages.pnpm
  ];
}
