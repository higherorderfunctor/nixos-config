{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.bruno];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/bruno")
    ];
  };
}
