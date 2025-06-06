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
      #
      # avoid aggressive memory use by the Nix store
      min-free = 10 * 1024 * 1024; # 10 MiB
      max-free = 200 * 1024 * 1024; # 200 MiB

      # let Nix auto-detect job count
      max-jobs = "auto";
      cores = 0; # use all available cores
    };
  };

  systemd.services.nix-daemon.serviceConfig = {
    MemoryAccounting = true;
    MemoryMax = "20G"; # Cap daemon memory usage
    OOMScoreAdjust = 500; # Prefer killing builds over system processes
  };

  sops.secrets."${username}-nix-conf-secrets" = {
    mode = "400";
    sopsFile = ../../../home/caubut/secrets/secrets.yaml;
  };
}
