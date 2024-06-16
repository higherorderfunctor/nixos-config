{
  config,
  lib,
  ...
}: let
  inherit (config.home) username;
in {
  programs.wezterm = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    # extraConfig = builtins.readFile ./wezterm-config/wezterm.lua;
  };
  xdg.configFile.wezterm = lib.mkForce {
    text = lib.mkForce null;
    source =
      config.lib.file.mkOutOfStoreSymlink
      "${config.xdg.userDirs.documents}/projects/nixos-config/home/${username}/features/desktop/wezterm/wezterm-config";
  };
}
# echo -e "\e[1mThis is bold text\e[0m"
# echo -e "\e[3mThis is italic text\e[0m"
# echo -e "\e[1;3mThis is bold italic text\e[0m"
