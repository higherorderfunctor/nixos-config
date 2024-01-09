_: let
  fast-syntax-highlighting = builtins.fetchTarball {
    url = "https://github.com/zdharma-continuum/fast-syntax-highlighting/archive/master.tar.gz";
    # sha256 = lib.fakeSha256;
    sha256 = "1bmrb724vphw7y2gwn63rfssz3i8lp75ndjvlk5ns1g35ijzsma5";
  };
in {
  xdg.configFile."zsh/plugins/fast-syntax-highlighting" = {
    source = fast-syntax-highlighting;
    recursive = true;
  };
}
