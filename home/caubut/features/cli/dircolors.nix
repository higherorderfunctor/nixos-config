{config, ...}: {
  programs.dircolors = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    # https://github.com/ss77a/Catppuccin-dircolors/blob/master/bliss.dircolors
    settings = {
      ## global defaults
      NORMAL = "00"; # no color
      RESET = "0"; # reset to "normal" color

      FILE = "00"; # normal
      DIR = "38;5;218;01"; # pink bg, bold
      LINK = "38;5;115"; # green
      MULTIHARDLINK = "04;38;5;115"; # green

      FIFO = "48;5;137"; # bronze bg, white
      SOCK = "48;5;137"; # bronze bg, white
      DOOR = "48;5;137"; # bronze bg, white
      BLK = "38;5;222;04"; # bronze bg, underscore
      CHR = "38;5;222;01"; # bronze, bold

      EXEC = "01"; # normal, bold

      OTHER_WRITABLE = "38;5;153;01"; # blue, bold
      STICKY = "48;5;67"; # blue bg, white
      STICKY_OTHER_WRITABLE = "48;5;30"; # teal bg, white

      ORPHAN = "48;5;167"; # red bg, white
      SETUID = "38;5;210;04"; # red, underscore
      SETGID = "38;5;180;04"; # bronze, underscore

      CAPABILITY = "00"; # white

      ## archive or compressed - lavender, bold
      ".tar" = "38;5;147;01";
      ".tgz" = "38;5;147;01";
      ".arj" = "38;5;147;01";
      ".taz" = "38;5;147;01";
      ".lzh" = "38;5;147;01";
      ".lzma" = "38;5;147;01";
      ".tlz" = "38;5;147;01";
      ".txz" = "38;5;147;01";
      ".zip" = "38;5;147;01";
      ".z" = "38;5;147;01";
      ".Z" = "38;5;147;01";
      ".dz" = "38;5;147;01";
      ".gz" = "38;5;147;01";
      ".lz" = "38;5;147;01";
      ".xz" = "38;5;147;01";
      ".bz2" = "38;5;147;01";
      ".bz" = "38;5;147;01";
      ".tbz" = "38;5;147;01";
      ".tbz2" = "38;5;147;01";
      ".tz" = "38;5;147;01";
      ".deb" = "38;5;147;01";
      ".rpm" = "38;5;147;01";
      ".jar" = "38;5;147;01";
      ".rar" = "38;5;147;01";
      ".ace" = "38;5;147;01";
      ".zoo" = "38;5;147;01";
      ".cpio" = "38;5;147;01";
      ".7z" = "38;5;147;01";
      ".rz" = "38;5;147;01";
      ".apk" = "38;5;147;01";
      ".gem" = "38;5;147;01";

      # general file - normal
      ".tex" = "00";
      ".rdf" = "00";
      ".owl" = "00";
      ".n3" = "00";
      ".ttl" = "00";
      ".nt" = "00";
      ".torrent" = "00";
      ".xml" = "00";
      "*Makefile" = "00";
      "*Rakefile" = "00";
      "*Dockerfile" = "00";
      "*build.xml" = "00";
      "*rc" = "00";
      "*1" = "00";
      ".nfo" = "00";
      "*README" = "00";
      "*README.txt" = "00";
      "*readme.txt" = "00";
      ".md" = "00";
      "*README.markdown" = "00";
      ".ini" = "00";
      ".yml" = "00";
      ".cfg" = "00";
      ".conf" = "00";
      ".h" = "00";
      ".hpp" = "00";
      ".c" = "00";
      ".cpp" = "00";
      ".cxx" = "00";
      ".cc" = "00";
      ".objc" = "00";
      ".sqlite" = "00";
      ".go" = "00";
      ".sql" = "00";
      ".csv" = "00";

      # image file - yellow
      ".jpg" = "38;5;229";
      ".JPG" = "38;5;229";
      ".jpeg" = "38;5;229";
      ".gif" = "38;5;229";
      ".bmp" = "38;5;229";
      ".pbm" = "38;5;229";
      ".pgm" = "38;5;229";
      ".ppm" = "38;5;229";
      ".tga" = "38;5;229";
      ".xbm" = "38;5;229";
      ".xpm" = "38;5;229";
      ".tif" = "38;5;229";
      ".tiff" = "38;5;229";
      ".png" = "38;5;229";
      ".PNG" = "38;5;229";
      ".svg" = "38;5;229";
      ".svgz" = "38;5;229";
      ".mng" = "38;5;229";
      ".pcx" = "38;5;229";
      ".dl" = "38;5;229";
      ".xcf" = "38;5;229";
      ".xwd" = "38;5;229";
      ".yuv" = "38;5;229";
      ".cgm" = "38;5;229";
      ".emf" = "38;5;229";
      ".eps" = "38;5;229";
      ".CR2" = "38;5;229";
      ".ico" = "38;5;229";

      # audio file - lime-green
      ".aac" = "38;5;193";
      ".au" = "38;5;193";
      ".flac" = "38;5;193";
      ".mid" = "38;5;193";
      ".midi" = "38;5;193";
      ".mka" = "38;5;193";
      ".mp3" = "38;5;193";
      ".mpc" = "38;5;193";
      ".ogg" = "38;5;193";
      ".opus" = "38;5;193";
      ".ra" = "38;5;193";
      ".wav" = "38;5;193";
      ".m4a" = "38;5;193";
      ".axa" = "38;5;193";
      ".oga" = "38;5;193";
      ".spx" = "38;5;193";
      ".xspf" = "38;5;193";

      # video file - orange
      ".mov" = "38;5;222";
      ".MOV" = "38;5;222";
      ".mpg" = "38;5;222";
      ".mpeg" = "38;5;222";
      ".m2v" = "38;5;222";
      ".mkv" = "38;5;222";
      ".ogm" = "38;5;222";
      ".mp4" = "38;5;222";
      ".m4v" = "38;5;222";
      ".mp4v" = "38;5;222";
      ".vob" = "38;5;222";
      ".qt" = "38;5;222";
      ".nuv" = "38;5;222";
      ".wmv" = "38;5;222";
      ".asf" = "38;5;222";
      ".rm" = "38;5;222";
      ".rmvb" = "38;5;222";
      ".flc" = "38;5;222";
      ".avi" = "38;5;222";
      ".fli" = "38;5;222";
      ".flv" = "38;5;222";
      ".gl" = "38;5;222";
      ".m2ts" = "38;5;222";
      ".divx" = "38;5;222";
      ".webm" = "38;5;222";
      ".axv" = "38;5;222";
      ".anx" = "38;5;222";
      ".ogv" = "38;5;222";
      ".ogx" = "38;5;222";

      # 'unimportant' file e.g. logs and backups - grey
      ".log" = "38;5;248";
      ".bak" = "38;5;248";
      ".aux" = "38;5;248";
      ".lof" = "38;5;248";
      ".lol" = "38;5;248";
      ".lot" = "38;5;248";
      ".out" = "38;5;248";
      ".toc" = "38;5;248";
      ".bbl" = "38;5;248";
      ".blg" = "38;5;248";
      "*~" = "38;5;248";
      "*#" = "38;5;248";
      ".part" = "38;5;248";
      ".incomplete" = "38;5;248";
      ".swp" = "38;5;248";
      ".tmp" = "38;5;248";
      ".temp" = "38;5;248";
      ".o" = "38;5;248";
      ".pyc" = "38;5;248";
      ".class" = "38;5;248";
      ".cache" = "38;5;248";
    };
  };
}
