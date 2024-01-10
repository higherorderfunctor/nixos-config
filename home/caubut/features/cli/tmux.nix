{
  config,
  pkgs,
  ...
}: let
  tmux-which-key =
    pkgs.tmuxPlugins.mkTmuxPlugin
    {
      pluginName = "tmux-which-key";
      version = "40998ea"; # short commit hash
      src = builtins.fetchTarball {
        url = "https://github.com/higherorderfunctor/tmux-which-key/archive/feat/xdg-dirs.tar.gz";
        # sha256 = lib.fakeSha256;
        sha256 = "0hc4f66c8cladrczbdyhlh8b8cy59s9jk2dpfmylrz8s615z4mns";
      };
      rtpFilePath = "plugin.sh.tmux";
    };
in {
  programs = {
    # TODO: https://github.com/junegunn/fzf#respecting-gitignore
    # TODO: https://github.com/rothgar/awesome-tmux
    # TODO: https://github.com/sainnhe/tmux-fzf
    tmux = {
      enable = true;
      package = pkgs.tmux;
      escapeTime = 10;
      historyLimit = 50000;
      keyMode = "vi";
      mouse = true;
      terminal = "screen-256color";
      extraConfig = ''
        set -as terminal-features ',rxvt-unicode-256color:clipboard'

        set-option -g focus-events on
      '';
      plugins = [
        {
          plugin = pkgs.tmuxPlugins.catppuccin;
          extraConfig = ''
            set -g @catppuccin_window_left_separator "█"
            set -g @catppuccin_window_right_separator "█ "
            set -g @catppuccin_window_number_position "right"
            set -g @catppuccin_window_middle_separator "  █"

            set -g @catppuccin_window_default_fill "number"

            set -g @catppuccin_window_current_fill "number"
            set -g @catppuccin_window_current_text "#{pane_current_path}"

            set -g @catppuccin_status_modules_right "application session date_time"
            set -g @catppuccin_status_left_separator  ""
            set -g @catppuccin_status_right_separator " "
            set -g @catppuccin_status_right_separator_inverse "yes"
            set -g @catppuccin_status_fill "all"
            set -g @catppuccin_status_connect_separator "no"
          '';
        }
        {
          plugin = tmux-which-key;
          extraConfig = ''
            set -g @tmux-which-key-enable-xdg-dirs 1;
          '';
        }
      ];
    };
    fzf.tmux = {
      enableShellIntegration = config.programs.fzf.enable;
      shellIntegrationOptions = ["-p 80%,60%"];
    };
  };
}
