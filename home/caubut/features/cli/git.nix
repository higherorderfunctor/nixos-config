{
  config,
  lib,
  pkgs,
  ...
}: let
  username = "${config.home.username}";
in {
  programs.git = {
    enable = true;
    package = pkgs.git;
    userName = "Christopher Aubut";
    userEmail = "christopher@aubut.me";
    extraConfig = {
      merge.tool = "nvim";
      mergetool = {
        prompt = false;
        nvim.cmd = "nvim -f -c \"Gdiffsplit!\" \"$MERGED\"";
      };
      pull.ff = "only";
      push.autoSetupRemote = true;
    };
    includes = [
      {
        path = "${config.xdg.configHome}/git/work.inc";
        condition = "gitdir:${config.xdg.userDirs.documents}/work";
      }
    ];
  };
  systemd.user.tmpfiles.rules = [
    "d ${config.xdg.userDirs.documents}/work 0700 ${username} ${username} - -"
  ];
  xdg.configFile."git/work.inc".source = lib.generators.toGitINI {
    userEmail = "christopher.aubut@charter.com";
  };
}
# TODO: checkout modern diff tool
