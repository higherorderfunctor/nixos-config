{pkgs, ...}: {
  home.packages = [pkgs.bitwarden-cli];
  # TODO: https://bitwarden.com/help/cli/
  # move or define config file
  # completions
  # # bitwarden
  # if command -v bw > /dev/null; then
  #   # TODO move to install script eval "$(bw completion --shell zsh); compdef _bw bw;"
  # fi
}
