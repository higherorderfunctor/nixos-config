{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.keybase-gui];
  services = {
    keybase.enable = true;
    kbfs.enable = true;
  };

  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/keybase")
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Keybase")
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/keybase")
    ];
  };
}
