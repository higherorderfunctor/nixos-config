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
      configDir =
        lib.mkDefault
        (lib.strings.removePrefix
          "${config.home.homeDirectory}"
          "${config.xdg.configHome}/eww");
    };
  };
  xdg.configFile.eww = lib.mForce {
    source = ./eww-config;
    recursive = true;
  };
}
