{config}: let
  configDir = "zsh/plugins/fast-syntax-highlighting";
  fast-syntax-highlighting = builtins.fetchTarball {
    url = "https://github.com/zdharma-continuum/fast-syntax-highlighting/archive/master.tar.gz";
    # sha256 = lib.fakeSha256;
    sha256 = "1bmrb724vphw7y2gwn63rfssz3i8lp75ndjvlk5ns1g35ijzsma5";
  };
in {
  programs.zsh.initExtra = ''
    # fast-syntax-highlighting
    source "${config.xdg.configDir}${configDir}/fast-syntax-highlighting.plugin.zsh"
  '';
  xdg.configFile."${configDir}" = {
    source = fast-syntax-highlighting;
    recursive = true;
  };
}
