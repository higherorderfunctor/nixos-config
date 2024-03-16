{
  config,
  lib,
  pkgs,
  ...
}: {
  home = {
    packages = [pkgs.slack];
    # persistence
    persistence = {
      "/persist${config.home.homeDirectory}".directories = [
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Slack")
      ];
    };
  };
}
