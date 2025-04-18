{
  config,
  lib,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  programs.zsh = {
    enable = true;
    package = pkgs.zsh;
    enableCompletion = true;
    completionInit = lib.strings.concatStringsSep " && " [
      "autoload -U compinit -d ${config.xdg.dataHome}/zsh/.zcompdump"
      "compinit -d ${config.xdg.dataHome}/zsh/.zcompdump"
    ];
    defaultKeymap = "viins";
    dotDir = lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/zsh";
    history = {
      path = "${config.xdg.dataHome}/zsh/zsh_history";
    };
    shellAliases = {
      grep = "grep -i --color=auto";
      ls = "ls --color=auto";
      l = "ls -lah";
      ll = "ls -lh";
      # TODO: opens in any terminal with tmux not one run from
      lb = "tmux popup -w 99% -h 99% -E 'findmnt -n | less'";
      nv = "${config.home.homeDirectory}/Documents/projects/nixos-config/scripts/nix-update";
      sw = "NIX_DEBUG=8 sudo nixos-rebuild --show-trace --option eval-cache false --flake \"${config.home.homeDirectory}/Documents/projects/nixos-config#$(hostname)\" switch"; # -b backup
      gc = "nix store gc";
      # git = "git-branchless wrap --";
    };
    # TODO: https://thevaluable.dev/zsh-completion-guide-examples/
    initExtraBeforeCompInit = ''
      # directory options
      setopt auto_cd
      setopt auto_pushd
      setopt pushd_ignore_dups
      setopt pushdminus

      # completion options
      unsetopt menu_complete   # do not autoselect the first completion entry
      unsetopt flowcontrol
      setopt auto_menu         # show completion menu on successive tab press
      setopt complete_in_word
      setopt always_to_end

      # history options
      setopt extended_history       # record timestamp of command in HISTFILE
      setopt hist_expire_dups_first # delete duplicates first when HISTFILE size exceeds HISTSIZE
      setopt hist_ignore_dups       # ignore duplicated commands history list
      setopt hist_ignore_space      # ignore commands that start with space
      setopt hist_verify            # show command with history expansistrings.concatMapStringson to user before running it
      setopt share_history          # share command history data

      # misc
      setopt multios              # enable redirect to multiple streams: echo >file1 >file2
      setopt long_list_jobs       # show long list format job notifications
      setopt interactivecomments  # recognize comments
      setopt promptsubst          # enable prompt expansion
      # setopt extended_glob      # more glob patterns - breaks nix expressions with #
    '';
    initExtra = ''
      zstyle ':completion:*:*:*:*:*' menu select

      autoload -U up-line-or-beginning-search
      zle -N up-line-or-beginning-search
      autoload -U down-line-or-beginning-search
      zle -N down-line-or-beginning-search

      bindkey "^[OA" up-line-or-beginning-search   # up arrow
      bindkey "^[OB" down-line-or-beginning-search # down arrow
      bindkey "^[OC" vi-forward-char               # right arrow
      bindkey "^[OD" vi-backward-char              # left arrow
      bindkey "^[[1;5C" forward-word               # ctrl + right arrow
      bindkey "^[[1;5D" backward-word              # ctrl + left arrow
      bindkey "^[[Z" reverse-menu-complete         # shift + tab
      bindkey "^?" backward-delete-char            # backspace

      # colors
      zstyle ':completion:*:default' list-colors ''${(s.:.)LS_COLORS}

      function git() { git-branchless wrap -- "$@" }
    '';
  };

  # permission fixes
  systemd.user.tmpfiles.rules = [
    "z ${config.xdg.dataHome}/zsh 0700 ${username} ${username} - -"
    "z /persist${config.xdg.dataHome}/zsh 0700 ${username} ${username} - -"
  ];

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/zsh")
    ];
  };
}
# TODO: use xdg everywhere
# TODO: oh-my-zsh = {
#   enable = true;
#   plugins = ["git"];
# };
#  awesome-zsh
#
#  https://www.reddit.com/r/commandline/comments/jhcuca/get_a_popup_completion_menu_in_zsh_with_fzftab/
#
#  completion from man pages
#
#
# # THIS IS GENERATED BY PNPM COMPLETEION INSTALL
# # tabtab source for packages
# # uninstall by removing these lines
# [[ -f ~/.config/tabtab/zsh/__tabtab.zsh ]] && . ~/.config/tabtab/zsh/__tabtab.zsh || true
#
# # pnpm
# export PNPM_HOME="/home/caubut/.local/share/pnpm"
# case ":$PATH:" in
#   *":$PNPM_HOME:"*) ;;
#   *) export PATH="$PNPM_HOME:$PATH" ;;
# esac
# # pnpm end
#
# # bun completions
# [ -s "/home/caubut/.bun/_bun" ] && source "/home/caubut/.bun/_bun"
#
# # bun
# export BUN_INSTALL="$HOME/.bun"
# export PATH="$BUN_INSTALL/bin:$PATH"
#
# TODO theme folders and other other outputs
