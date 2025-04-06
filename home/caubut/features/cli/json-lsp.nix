{pkgs, ...}: {
  home.packages = [
    pkgs.nodePackages.vscode-json-languageserver
  ];
}
