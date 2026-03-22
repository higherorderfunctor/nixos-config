{
  config,
  lib,
  pkgs,
  ...
}: {
  imports = [../../../../hosts/common/shared];

  nix = {
    gc = {
      dates = "weekly";
    };
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

  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nix") # repl history
    ];
  };
}
