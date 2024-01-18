{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  programs = {
    eww = {
      enable = true;
      package = inputs.eww.packages.${pkgs.system}.eww;
      configDir = {
        source = ./eww-config;
        recursive = true;
      }; # TODO:
    };
  };
}
