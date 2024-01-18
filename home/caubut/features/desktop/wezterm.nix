{config, ...}: {
  programs.wezterm = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
  };
}
