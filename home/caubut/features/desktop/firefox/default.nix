{pkgs, ...}: {
  programs.firefox = {
    enable = true;
    packges = pkgs.latest.firefox-nightly-bin;
  };
}
