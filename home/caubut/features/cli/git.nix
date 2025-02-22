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
    # signing.format = "ssh";
    extraConfig = {
      init.defaultBranch = "main";
      merge.tool = "diffview";
      mergetool = {
        prompt = false;
        diffview.cmd = ''nvim -n -c "DiffviewOpen" "$MERGE"'';
      };
      pull.ff = "only";
      push.autoSetupRemote = true;
    };
    includes = [
      {
        path = "${config.xdg.configHome}/git/work.inc";
        condition = "gitdir:${config.xdg.userDirs.documents}/work/";
      }
    ];
  };
  xdg.configFile."git/work.inc".text = lib.generators.toGitINI {
    user.email = "christopher.aubut@charter.com";
  };
  systemd.user.tmpfiles.rules = [
    # TODO: fix permissions on other files
    "d ${config.xdg.userDirs.documents}/work 0700 ${username} ${username} - -"
  ];
}
