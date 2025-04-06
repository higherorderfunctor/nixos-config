{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.awscli2];

  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.home.homeDirectory}/.aws")
    ];
  };
}
