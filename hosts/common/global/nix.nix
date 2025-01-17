{
  lib,
  config,
  ...
}: let
  username = "caubut";
in {
  nix = lib.mkMerge [
    lib.shared.config.nix
    {
      gc = {
        dates = "weekly";
      };
      extraOptions = ''
        !include ${config.sops.secrets."${username}-nix-conf-secrets".path}
      '';
    }
  ];

  sops.secrets."${username}-nix-conf-secrets" = {
    mode = "400";
    sopsFile = ../../../home/caubut/secrets/secrets.yaml;
  };
}
