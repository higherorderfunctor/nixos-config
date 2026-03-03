{
  config,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  programs.wezterm = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    extraConfig = ''
      return dofile(wezterm.config_dir .. "/wezterm-config/init.lua")
    '';
  };
  home.packages = with pkgs; [
    wezter.terminfo
  ];
  xdg.configFile."wezterm/wezterm-config" = {
    source =
      config.lib.file.mkOutOfStoreSymlink
      "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/desktop/wezterm/wezterm-config";
  };
}
