{
  config,
  lib,
  ...
}: {
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
