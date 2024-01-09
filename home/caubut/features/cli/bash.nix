{config, ...}: {
  programs.bash = {
    enable = true;
    historyFile = {
      path = "${config.xdg.dataHome}/bash/bash_history";
    };
  };
}
