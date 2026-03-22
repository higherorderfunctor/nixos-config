{
  config,
  lib,
  pkgs,
  ...
}: let
  username = "${config.home.username}";
in {
  home.packages = with pkgs; [git-absorb git-branchless git-revise dprint];
  programs.git = {
    enable = true;
    package = pkgs.git;
    # signing.format = "ssh";
    settings = {
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
      absorb = {
        fixupTargetAlwaysSHA = true;
        maxStack = 50;
        oneFixupPerCommit = true;
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
      paging = {
        colorArg = "always";
        pager = "delta --dark --paging=never";
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
  };
  programs.delta = {
    enable = true;
    enableGitIntegration = true;
  };
  systemd.user.tmpfiles.rules = [
    # TODO: fix permissions on other files
    "d ${config.xdg.userDirs.documents}/work 0700 ${username} ${username} - -"
  ];
}
