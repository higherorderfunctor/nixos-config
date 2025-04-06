{pkgs, ...}: {
  # patched fonts with icons # FIXME: not checked
  home.packages = with pkgs; with nerd-fonts; [ubuntu monaspace];
}
