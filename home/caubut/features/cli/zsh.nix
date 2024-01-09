{
  config,
  pkgs,
  ...
}: {
  programs.zsh = {
    enable = true;
    package = pkgs.zsh;
    defaultKeymap = "viins";
    history = {
      path = "${config.xdg.dataHome}/zsh/zsh_history";
    };
  };
}
# oh-my-zsh = {
#   enable = true;
#   plugins = ["git"];
# };
