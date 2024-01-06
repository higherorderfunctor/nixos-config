{pkgs, ...}: {
  programs = {
    zsh = {
      enable = true;
      package = pkgs.zsh;
      oh-my-zsh = {
        enable = true;
        plugins = ["git"];
      };
    };
    fzf = {
      enable = true;
      package = pkgs.fzf;
      enableZshIntegration = true;
      colors = {
        "bg+" = "#313244";
        bg = "#1e1e2e";
        spinner = "#f5e0dc";
        hl = "#f38ba8";
        fg = "#cdd6f4";
        header = "#f38ba8";
        info = "#cba6f7,";
        pointer = "#f5e0dc";
        marker = "#f5e0dc";
        "fg+" = "#cdd6f4";
        prompt = "#cba6f7";
        "hl+" = "#f38ba8";
        # https://github.com/catppuccin/fzf
        # --color=bg+:#313244,bg:#1e1e2e,spinner:#f5e0dc,hl:#f38ba8 \
        # --color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
        # --color=marker:#f5e0dc,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8"
      };
    };
    oh-my-posh = {
      enable = true;
      settings =
        builtins.fromJSON
        (builtins.unsafeDiscardStringContext
          (builtins.readFile ./catppuccin.omp.json));
    };
  };
}
