{...}: {
  imports = [../../common/shared];

  nix = {
    gc = {
      dates = "weekly";
    };
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
}
