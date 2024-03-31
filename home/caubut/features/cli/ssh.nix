{
  config,
  lib,
  ...
}: {
  services = {
    ssh-agent.enable = true;
  };

  # TODO: possible fix for known hosts? https://nixos.wiki/wiki/Home_Manager#Workaround_with_home_on_tmpfs_and_standalone_installation
  programs = {
    ssh = {
      enable = true;
      addKeysToAgent = "yes";
      matchBlocks = {
        "github.com" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/personal_ed25519_key";
          # identityFile = config.sops.secrets."${config.home.username}-personal-ed25519-key".path;
        };
        "github-professional" = {
          hostname = "github.com";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/professional_ed25519_key";
          # identityFile = config.sops.secrets."${config.home.username}-professional-ed25519-key".path;
        };
        "gitlab.spectrumflow.net" = {
          hostname = "gitlab.spectrumflow.net";
          user = "git";
          identityFile = "/home/${config.home.username}/.ssh/professional_ed25519_key";
          # identityFile = config.sops.secrets."${config.home.username}-professional-ed25519-key".path;
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
      # TODO: re-evaluate this at some point
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
