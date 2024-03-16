_: let
  lessConfig = "-aRix2 --use-color --mouse --wheel-lines=3";
  # a = search from current position
  # i = case insensitive
  # x2 = tabstop
  # R = color control chars show color
in {
  programs.less.enable = true;
  home.sessionVariables = {
    LESS = lessConfig;
    SYSTEMD_LESS = lessConfig;
  };
}
# TODO
#open3: exec of vim -RXZ -i NONE -u NONE -N -n +set nomodeline chrome/userChrome.css -s /tmp/vimcolorICKy/scriptfile failed: No such file or directory at /nix/store/0m37plpfadr7l63mw546az2p4mm1xanv-lesspipe-2.11/bin/vimcolor line 244.
# TODO: systemd less test
# TODO: move from env to file?
# https://github.com/microsoft/vscode/issues/194630
