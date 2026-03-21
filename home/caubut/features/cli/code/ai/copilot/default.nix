{pkgs, ...}: {
  programs.gh = {
    enable = true;
    gitCredentialHelper.enable = false;
    settings = {
      git_protocol = "ssh";
    };
  };

  home.packages = [
    pkgs.github-copilot-cli
  ];
}
