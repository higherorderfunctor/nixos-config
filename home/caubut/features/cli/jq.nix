{pkgs, ...}: {
  programs.jq = {
    enable = true;
    package = pkgs.jq;
  };
  home.packages = with pkgs; [
    yq-go
  ];
}
