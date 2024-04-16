{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.discord];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/discord")
    ];
  };
}
