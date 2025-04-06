{pkgs, ...}: {
  home.packages = [pkgs.keybase];
  services.keybase.enable = true;
  services.kbfs.enable = true;
}
