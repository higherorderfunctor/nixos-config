{config, ...}: {
  programs.zellij = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    settings = {
      theme = "catppuccin-mocha";
      scroll_buffer_size = 50000;
      # layout_dir
      ui = {
        pane_frames = {
          hide_session_name = true;
          rounded_corners = true;
          pane_viewport_serialization = true;
          scrollback_lines_to_serialize = 0;
        };
      };
    };
  };
}
