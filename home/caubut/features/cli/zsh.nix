{
  config,
  lib,
  pkgs,
  ...
}:
with lib; let
  dataHome = "${config.xdg.dataHome}/zsh";
in {
  programs.zsh = {
    enable = true;
    package = pkgs.zsh;
    enableCompletion = true;
    completionInit = "autoload -U compinit -d ${dataHome}/.zcompdump && compinit -d ${dataHome}/.zcompdump";
    defaultKeymap = "viins";
    dotDir = ".config/zsh";
    history = {
      path = "${dataHome}/zsh_history";
    };
    # TODO: FIX ZCOMPDUMP GOING TO CONFIG
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
      setopt hist_verify            # show command with history expansion to user before running it
      setopt share_history          # share command history data

      # misc
      setopt multios              # enable redirect to multiple streams: echo >file1 >file2
      setopt long_list_jobs       # show long list format job notifications
      setopt interactivecomments  # recognize comments
      setopt promptsubst          # enable prompt expansion
    '';
  };
  # caching
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (strings.removePrefix "${config.home.homeDirectory}/" dataHome)
    ];
  };
}
# TODO: oh-my-zsh = {
#   enable = true;
#   plugins = ["git"];
# };
