{
  config,
  lib,
  pkgs,
  ...
}: let
  inherit (config.home) username;
in {
  imports = [../../../../hosts/common/shared];

  nix = {
    gc = {
      frequency = "weekly";
    };
    extraOptions = ''
      !include ${config.sops.secrets."${username}-nix-conf-secrets".path}
    '';
    settings = {
      # substituters = lib.mkForce null;

      # avoid aggressive memory use by the Nix store
      min-free = 10 * 1024 * 1024; # 10 MiB
      max-free = 200 * 1024 * 1024; # 200 MiB

      # let Nix auto-detect job count
      max-jobs = "auto";
      cores = 0; # use all available cores
    };
  };

  sops.secrets = {
    "${username}-nix-conf-secrets" = {
      mode = "400";
    };
  };

  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nix") # repl history
    ];
  };
  #  nix = lib.mkMerge [
  #    lib.shared.config.nix
  #    {
  #      gc = {
  #        frequency = "weekly";
  #      };
  #      extraOptions = ''
  #        !include ${config.sops.secrets."${config.home.username}-nix-conf-secrets".path}
  #      '';
  #    }
  #  ];
  #
  #  sops.secrets = {
  #    "${config.home.username}-nix-conf-secrets" = {
  #      mode = "400";
  #    };
  #  };
  #
  #  home.persistence = {
  #    "/persist${config.home.homeDirectory}".directories = [
  #      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nix") # repl history
  #    ];
  #  };
}
