{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.bitwarden-desktop];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Bitwarden")
    ];
  };
}
