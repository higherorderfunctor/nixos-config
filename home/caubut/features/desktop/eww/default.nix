{
  inputs,
  pkgs,
  ...
}: {
  programs = {
    eww.enable = true;
    package = inputs.eww.packages.${pkgs.system}.eww;
  };
  xdg.configFile.eww.source = {
    path = ./eww;
    recursive = true;
  };
}
