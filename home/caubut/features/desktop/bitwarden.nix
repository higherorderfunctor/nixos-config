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
# TODO: node:125650) UnhandledPromiseRejectionWarning: TypeError: Cannot read properties of undefined (reading 'setContextMenu')
