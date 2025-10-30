{
  config,
  lib,
  pkgs,
  ...
}: let
  slackWithDisableGpu = pkgs.symlinkJoin {
    name = "slack-with-disable-gpu";
    paths = [pkgs.slack];
    buildInputs = [pkgs.makeWrapper];
    postBuild = ''
      wrapProgram $out/bin/slack \
        --add-flags --disable-gpu
    '';
  };
in {
  home = {
    packages = [slackWithDisableGpu];
    persistence = {
      "/persist${config.home.homeDirectory}".directories = [
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Slack")
      ];
    };
  };
}
