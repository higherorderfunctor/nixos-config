{
  config,
  pkgs,
  inputs,
  ...
}: {
  # imports = [
  #   ../../../../../modules/home-manager/tmux-which-key.nix
  # ];

  imports = [inputs.tmux-which-key.homeManagerModules.default];

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
      tmux-which-key = {
        enable = true;
        settings = import ./tmux-which-key-config.nix;
      };
      escapeTime = 10;
      historyLimit = 50000;
      keyMode = "vi";
      mouse = true;
      terminal = "tmux-256color";
      extraConfig = ''
        set-option -g focus-events on

        bind-key -T copy-mode-vi 'v' send -X           begin-selection

        if-shell -b 'echo $XDG_SESSION_TYPE | grep -q x11' "\
            bind-key -T copy-mode-vi MouseDragEnd1Pane send-keys -X copy-pipe-and-cancel 'xclip -i -f -selection primary | xclip -i -selection clipboard'; \
            bind-key -T copy-mode-vi Enter             send-keys -X copy-pipe-and-cancel 'xclip -i -f -selection primary | xclip -i -selection clipboard'; \
            bind-key -T copy-mode-vi 'y'               send-keys -X copy-pipe-and-cancel 'xclip -i -f -selection primary | xclip -i -selection clipboard';"

        if-shell -b 'echo $XDG_SESSION_TYPE | grep -q wayland' "\
            bind-key -T copy-mode-vi MouseDragEnd1Pane send-keys -X copy-pipe-and-cancel 'wl-copy'; \
            bind-key -T copy-mode-vi Enter             send-keys -X copy-pipe-and-cancel 'wl-copy'; \
            bind-key -T copy-mode-vi 'y'               send-keys -X copy-pipe-and-cancel 'wl-copy';"
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
      ];
    };
    fzf.tmux = {
      enableShellIntegration = config.programs.fzf.enable;
      shellIntegrationOptions = ["-p 80%,60%"];
    };
  };
}
