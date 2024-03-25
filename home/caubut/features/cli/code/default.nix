{pkgs, ...}: {
  imports = [
    ./docker.nix
    ./markdown.nix
    ./openapi.nix
    ./yaml.nix
  ];

  home.packages = with pkgs; [
    # vscode-css-language-server
    # vscode-eslint-language-server
    # vscode-html-language-server
    # vscode-json-language-server
    # vscode-markdown-language-server
    vscode-langservers-extracted
  ];
}
