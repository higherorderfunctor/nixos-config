{
  inputs,
  pkgs,
  ...
}: {
  programs = {
    eww = {
      enable = true;
      package = inputs.eww.packages.${pkgs.system}.eww;
      configDir = ./.config/eww; # TODO:
    };
  };
  xdg.configFile.eww.source = {
    path = ./eww-config;
    recursive = true;
  };
}
