{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.signal-desktop];

  # persistence
  persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Signal")
    ];
  };
}
