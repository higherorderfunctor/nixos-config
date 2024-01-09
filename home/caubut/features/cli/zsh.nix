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
    defaultKeymap = "viins";
    dotDir = ".config/zsh";
    completionInit = "autoload -U compinit -d ${dataHome}/.zcompdump && compinit -d ${dataHome}/.zcompdump";
    history = {
      path = "${dataHome}/zsh_history";
    };
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
