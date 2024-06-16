
  tmux-which-key =
    pkgs.tmuxPlugins.mkTmuxPlugin
    {
      pluginName = "tmux-which-key";
      version = "2024-01-11-1";
      src = pkgs.fetchFromGitHub {
        owner = "alexwforsythe";
        repo = "tmux-which-key";
        rev = "a6a460e587ef5006e10ac372ad9dbbcd286b11cc";
        sha256 = "sha256-EvBehGaxMHJq68qdhsfEnTeUTR4G29vyIw0YJmqbwrc=";
      };
      rtpFilePath = "plugin.sh.tmux";
    };
