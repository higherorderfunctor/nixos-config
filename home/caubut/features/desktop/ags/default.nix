{
  inputs,
  lib,
  pkgs,
  ...
}: {
  # add the home manager module
  imports = [inputs.ags.homeManagerModules.default];

  programs.ags = {
    enable = true;

    # null or path, leave as null if you don't want hm to manage the config
    # configDir = ../ags;

    # additional packages to add to gjs's runtime
    extraPackages = [pkgs.libsoup_3];
  };

  xdg.configFile.ags = lib.mkForce {
    source = ./ags-config;
    recursive = true;
  };
}