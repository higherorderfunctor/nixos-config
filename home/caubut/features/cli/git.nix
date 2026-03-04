{
  config,
  lib,
  pkgs,
  ...
}: let
  username = "${config.home.username}";
in {
  home.packages = with pkgs; [git-branchless dprint];
  sops.secrets = {
    "${username}-github-api-key" = {
      mode = "400";
    };
  };
  programs.git = {
    enable = true;
    package = pkgs.git;
    # signing.format = "ssh";
    settings = {
      credential."https://github.com" = {
        helper = ''
          !f() { echo "username=x-access-token"; echo "password=$(cat ${config.sops.secrets."caubut-github-api-key".path})"; }; f
        '';
      };
      user = {
        name = "Christopher Aubut";
        email = "christopher@aubut.me";
      };
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
    includes = [
      {
        path = "${config.xdg.configHome}/git/work.inc";
        condition = "gitdir:${config.xdg.userDirs.documents}/work/";
      }
    ];
  };
  programs.delta = {
    enable = true;
    enableGitIntegration = true;
  };
  xdg.configFile."git/work.inc".text = lib.generators.toGitINI {
    user.email = "christopher.aubut@charter.com";
  };
  systemd.user.tmpfiles.rules = [
    # TODO: fix permissions on other files
    "d ${config.xdg.userDirs.documents}/work 0700 ${username} ${username} - -"
  ];
}
