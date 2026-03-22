{pkgs, ...}: {
  programs.gh = {
    enable = true;
    # disabled: conflicts with sops-managed credential helper in git.nix
    gitCredentialHelper.enable = false;
    settings = {
      git_protocol = "ssh";
    };
  };

  home.packages = [
    pkgs.github-copilot-cli
  ];
}
