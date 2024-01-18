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
      # Required to be set to something symlinked to .config/eww by the eww module.
      # Not needed as .config/eww will be populated through xdg to load the files.
      configDir =
        lib.mkDefault
        (lib.strings.removePrefix
          "${config.home.homeDirectory}"
          "${config.xdg.configHome}/eww");
    };
  };
  # override the symlink eww sets up
  xdg.configFile.eww = lib.mkForce {
    source = ./eww-config;
    recursive = true;
  };
}
