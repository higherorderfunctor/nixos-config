{config, ...}: {
  services = {
    ssh-agent.enable = true;
  };
  programs = {
    ssh = {
      enable = true;
      addKeysToAgent = "yes";
      extraConfig = ''
        IdentityFile /home/${config.home.username}/.ssh/personal_ed25519_key
      '';
      matchBlocks = {
        "github.com" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/personal_ed25519_key";
        };
        "github.com-professional" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/professional_ed25519_key";
        };
        "gitlab.spectrumflow.net" = {
          hostname = "gitlab.spectrumflow.net";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/professional_ed25519_key";
        };
      };
    };
  };
}
