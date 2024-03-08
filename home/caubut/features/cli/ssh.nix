_: {
  services = {
    ssh-agent.enable = true;
  };
  programs = {
    ssh = {
      enable = true;
      addKeysToAgent = "yes";
      matchBlocks = {
        "github.com" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/username/.ssh/personal_ed25519_key";
        };
        "github.com-professional" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/username/.ssh/professional_ed25519_key";
        };
      };
    };
  };
}
