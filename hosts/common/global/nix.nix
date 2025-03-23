{
  config,
  inputs,
  ...
}: let
  username = "caubut";
in {
  imports = [inputs.sops-nix.nixosModules.sops ../../common/shared];

  nix = {
    gc = {
      dates = "weekly";
    };
    extraOptions = ''
      !include ${config.sops.secrets."${username}-nix-conf-secrets".path}
    '';
    settings = {
      #trusted-substituters = lib.mkForce null;
    };
  };

  sops.secrets."${username}-nix-conf-secrets" = {
    mode = "400";
    sopsFile = ../../../home/caubut/secrets/secrets.yaml;
  };
}
