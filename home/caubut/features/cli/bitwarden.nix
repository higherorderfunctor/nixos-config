{
  config,
  lib,
  pkgs,
  ...
}: {
  home.packages = [pkgs.bitwarden-cli];
  # TODO: https://bitwarden.com/help/cli/
  # move or define config file
  # completions
  # # bitwarden
  # if command -v bw > /dev/null; then
  #   # TODO move to install script eval "$(bw completion --shell zsh); compdef _bw bw;"
  # fi
  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.configHome}/Bitwarden CLI")
    ];
  };
}
