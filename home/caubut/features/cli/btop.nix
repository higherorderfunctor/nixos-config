{pkgs, ...}: {
  programs.btop = {
    enable = true;
    package = pkgs.btop;
    settings = {
      color_theme = "catppuccin_mocha";
      theme_background = false;
      clock_format = "%a, %b %m %Y %I:%M %p";
    };
  };
  xdg.configFile."btop/themes" = {
    source = pkgs.catppuccin-btop;
    recursive = true;
  };
}
