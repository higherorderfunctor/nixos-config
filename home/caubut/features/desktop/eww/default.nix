{
  inputs,
  pkgs,
  ...
}: {
  programs = {
    eww.enable = true;
    packge = inputs.eww.packages.${pkgs.system}.eww;
  };
  xdg.configFile.eww.source = {
    path = ./eww;
    recursive = true;
  };
}
