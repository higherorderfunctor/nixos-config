{config, ...}: {
  programs.bash = {
    enable = true;
    historyFile = "${config.xdg.dataHome}/bash/bash_history";
  };
}
# TODO: https://hiphish.github.io/blog/2020/12/27/making-bash-xdg-compliant/
