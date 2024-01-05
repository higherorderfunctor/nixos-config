{...}: {
  home.file."./.dotfiles/" = builtins.fetchGit {
    url = "https://github.com/higherorderfunctor/dotfiles";
    rev = "4b2d2fbb3ec6fa630ed236fe8fdef400ec1ab3f5";
  };
}
