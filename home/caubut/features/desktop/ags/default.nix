{
  inputs,
  lib,
  ...
}: {
  imports = [inputs.ags.homeManagerModules.default];

  programs.ags = {
    enable = true;

    # additional packages to add to gjs's runtime
    #extraPackages = [pkgs.libsoup_3];
  };

  xdg.configFile.ags = lib.mkForce {
    source = ./ags-config;
    recursive = true;
  };
}
