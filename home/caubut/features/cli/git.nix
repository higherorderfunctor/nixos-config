{
  config,
  lib,
  pkgs,
  ...
}: let
  username = "${config.home.username}";
in {
  home.packages = with pkgs; [git-branchless];
  programs.git = {
    enable = true;
    package = pkgs.git;
    userName = "Christopher Aubut";
    userEmail = "christopher@aubut.me";
    # signing.format = "ssh";
    extraConfig = {
      column.ui = "auto";
      branch.sort = "-committerdate";
      branchless = {
        core = {
          mainBranch = "main";
        };
        smartlog = {
          defaultRevset = "(@ % main()) | stack() | descendants(@) | @";
          # ((draft() | branches() | @) % main()) | branches() | @
        };
      };
      commit.verbose = true;
      core = {
        autocrlf = "input";
        fsmonitor = true;
        untrackedCache = true;
      };
      diff = {
        algorithm = "histogram";
        colorMoved = "plain";
        # NOTE: i/ (index), w/ (working directory), c/ commit
        mnemonicPrefix = true;
        renames = true;
      };
      fetch = {
        all = true;
        prune = true;
        pruneTags = true;
      };
      help.autocorrect = "prompt";
      init.defaultBranch = "main";
      tag.sort = "version:refname";
      merge = {
        conflictStyle = "zdiff3";
        tool = "diffview";
      };
      mergetool = {
        prompt = false;
        diffview.cmd = ''nvim -n -c "DiffviewOpen" "$MERGE"'';
      };
      pull = {
        ff = "only";
        rebase = true;
      };
      push = {
        autoSetupRemote = true;
        default = "simple";
        followTags = true;
      };
      rebase = {
        autoStash = true;
        autoSquash = true;
        updateRefs = true;
      };
      rerere = {
        enabled = true;
        autoupdate = true;
      };
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
