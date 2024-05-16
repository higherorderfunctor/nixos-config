{pkgs, ...}: {
  programs.hyprlock = {
    enable = true;
    package = pkgs.hyprlock;

    settings = {
      source = [
        "${pkgs.catppuccin-hyprland}/mocha.conf"
        "${pkgs.catppuccin-hyprlock}/hyprlock.conf"
      ];
      background = {
        path = "";
      };
    };
  };
}
