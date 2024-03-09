{
  config,
  lib,
  ...
}: {
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

  home = {
    file =
      {
        ".ssh/personal_ed25519_key.pub".source = ../../secrets/personal_ed25519_key.pub;
        ".ssh/professional_ed25519_key.pub".source = ../../secrets/professional_ed25519_key.pub;
      }
      # read from system unlocked secrets when nixos
      // lib.optionalAttrs (!config.targets.genericLinux.enable) {
        ".ssh/personal_ed25519_key".source =
          config.lib.file.mkOutOfStoreSymlink
          "/run/secrets/${config.home.username}-personal-ed25519-key";
      };
  };

  sops = {
    secrets =
      {
        "${config.home.username}-professional-ed25519-key" = {
          path = "${config.home.homeDirectory}/.ssh/professional_ed25519_key";
          mode = "400";
        };
      }
      # read from home manager unlocked secrets when not nixos
      # note: see sops.nix for starter key placement
      // lib.optionalAttrs config.targets.genericLinux.enable {
        "${config.home.username}-personal-ed25519-key" = {
          path = "${config.home.homeDirectory}/.ssh/personal_ed25519_key";
          mode = "400";
        };
      };
  };
}
