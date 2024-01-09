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
    completionInit = "autoload -U compinit -d ${dataHome} && compinit -d ${dataHome}";
    history = {
      path = "${dataHome}/zsh_history";
    };
  };
}
# oh-my-zsh = {
#   enable = true;
#   plugins = ["git"];
# };
