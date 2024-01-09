{
  config,
  pkgs,
  ...
}: let
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
    "/persist/${config.home.homeDirectory}".directories = [dataHome];
  };
}
# TODO: oh-my-zsh = {
#   enable = true;
#   plugins = ["git"];
# };
