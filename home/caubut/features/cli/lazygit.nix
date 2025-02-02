{
  config,
  lib,
  pkgs,
  ...
}: {
  programs.lazygit = {
    enable = true;
    package = pkgs.lazygit;
    settings = {
      disableStartupPopups = true;
    };
  };

  home = {
    file = {
      "${lib.strings.removePrefix
        "${config.home.homeDirectory}/"
        config.xdg.userDirs.documents}/work/.config/lazygit/config.yml".source =
        config.lib.file.mkOutOfStoreSymlink
        "${config.xdg.configHome}/lazygit/config.yml";
      "${lib.strings.removePrefix
        "${config.home.homeDirectory}/"
        config.xdg.userDirs.documents}/work/.config/git".source =
        config.lib.file.mkOutOfStoreSymlink
        "${config.xdg.configHome}/git";
    };
  };
}
