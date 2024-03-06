{
  config,
  lib,
  pkgs,
  ...
}: let
  # TODO: fix me
  tmux-which-key =
    pkgs.tmuxPlugins.mkTmuxPlugin
    {
      pluginName = "tmux-which-key";
      version = "2024-01-11-1";
      src = pkgs.fetchFromGitHub {
        owner = "alexwforsythe";
        repo = "tmux-which-key";
        rev = "a6a460e587ef5006e10ac372ad9dbbcd286b11cc";
        sha256 = "sha256-EvBehGaxMHJq68qdhsfEnTeUTR4G29vyIw0YJmqbwrc=";
      };
      rtpFilePath = "plugin.sh.tmux";
    };
  # TODO: python build step
in {
  xdg.configFile."tmux/plugins/tmux-which-key/config.yaml".text = lib.generators.toYAML {} {
    command_alias_start_index = 200;
    # rest of config here
  };
  programs = {
    # TODO: https://github.com/junegunn/fzf#respecting-gitignore
    # TODO: https://github.com/rothgar/awesome-tmux
    # TODO: https://github.com/sainnhe/tmux-fzf
    # set-option -g default-terminal "screen-256color"
    # set -g default-terminal "wezterm"
    # set -as terminal-features ",gnome*:RGB"
    # set -ag terminal-overrides ",xterm-256color:RGB"
    tmux = {
      enable = true;
      package = pkgs.tmux;
      escapeTime = 10;
      historyLimit = 50000;
      keyMode = "vi";
      mouse = true;
      terminal = "screen-256color";
      extraConfig = ''
        set-option -g focus-events on

        bind-key -T copy-mode-vi MouseDragEnd1Pane send-keys -X copy-pipe-and-cancel "xclip -i -f -selection primary | xclip -i -selection clipboard"
        bind-key -T copy-mode-vi Enter             send-keys -X copy-pipe-and-cancel "xclip -i -f -selection primary | xclip -i -selection clipboard"
        bind-key -T copy-mode-vi 'y'               send-keys -X copy-pipe-and-cancel "xclip -i -f -selection primary | xclip -i -selection clipboard"
        bind-key -T copy-mode-vi 'v' send -X       begin-selection
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
            set -g @tmux-which-key-xdg-enable 1;
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
