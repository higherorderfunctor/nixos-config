{
  config,
  lib,
  pkgs,
  ...
}: let
  tmux-which-key =
    pkgs.tmuxPlugins.mkTmuxPlugin
    {
      pluginName = "tmux-which-key";
      version = "2024-01-10";
      src = pkgs.fetchFromGitHub {
        owner = "higherorderfunctor";
        repo = "tmux-which-key";
        rev = "61db8ba0a0978b2d7901073099b49da57e9965b7";
        sha256 = "sha256-2lbySzAa/Ux9dbeJKZNOxTO0EKTQt/VZbooyxIxxhEE=";
      };
      rtpFilePath = "plugin.sh.tmux";
    };
in {
  xdg.configFile."tmux/plugins/tmux-which-key/config.yaml".text = lib.generators.toYAML {} {
    command_alias_start_index = 200;
    # rest of config here
  };
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
