{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.standardnotes];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Standard Notes")
    ];
  };
}
