{pkgs, ...}: {
  # allows you read and control device brightness # FIXME: not tested
  home.packages = [pkgs.brightnessctl];
}
