{pkgs, ...}: {
  programs.chromium = {
    enable = true;
    dictionaries = [pkgs.hunspellDictsChromium.en_US];
    package = pkgs.ungoogled-chromium;
  };
}
