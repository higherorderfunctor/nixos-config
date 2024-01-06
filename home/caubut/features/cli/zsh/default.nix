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
    oh-my-posh = {
      enable = true;
      settings =
        builtins.fromJSON
        (builtins.unsafeDiscardStringContext
          (builtins.readFile ./catppuccin.omp.json));
    };
  };
}
