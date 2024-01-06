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
      package = pkgs.oh-my-posh.override (prev: {
        oh-my-posh = prev.oh-my-posh.overrideAttrs (_: let
          version = "19.4.0";
        in {
          inherit version;
          src = pkgs.fetchFromGitHub {
            owner = "jandedobbeleer";
            repo = "oh-my-posh";
            rev = "refs/tags/v${version}";
            hash = "sha256-8MK8YzBplbP1de8QKJJBLgbMd1K+H2sVutwKSskU82Q=";
          };
          vendorHash = "sha256-ivd30IEoF9WuGDzufIOXJ8LUqHp3zPaiPgplj9jqzqw=";
        });
      });
      settings =
        builtins.fromJSON
        (builtins.unsafeDiscardStringContext
          (builtins.readFile ./catppuccin.omp.json));
    };
  };
}
