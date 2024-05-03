{
  config,
  lib,
  pkgs,
  ...
}: {
  # defaults for non-nixos systems
  nix = lib.mkDefault {
    package = pkgs.nix;
    settings = {
      trusted-users = ["root" "@wheel"];
      auto-optimise-store = lib.mkDefault true;
      experimental-features = ["nix-command" "flakes" "repl-flake"];
      access-tokens = [];
      trusted-substituters = [
        "https://nix-community.cachix.org"
        "https://cache.nixos.org/"
        "https://hyprland.cachix.org"
      ];
      trusted-public-keys = [
        "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
        "hyprland.cachix.org-1:a7pgxzMz7+chwVL3/pzj6jIBMioiJM7ypFP8PwtkuGc="
      ];
    };
    gc = {
      automatic = true;
      frequency = "weekly";
      # Keep the last 60 days of generations
      options = "--delete-older-than 60d";
    };
    extraOptions = ''
      !include ${config.sops.secrets."${config.home.username}-nix-conf-secrets".path}
    '';
  };
  sops.secrets = {
    "${config.home.username}-nix-conf-secrets" = {
      mode = "400";
    };
  };

  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/nix") # repl history
    ];
  };
}
