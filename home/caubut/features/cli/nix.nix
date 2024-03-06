{
  config,
  lib,
  pkgs,
  ...
}: {
  nix = {
    package = pkgs.nix;
    settings = {
      trusted-users = ["root" "@wheel" config.home.username];
      auto-optimise-store = lib.mkDefault true;
      experimental-features = ["nix-command" "flakes" "repl-flake"];
      substituters = [
        # "https://hyprland.cachix.org"
        "https://nix-community.cachix.org"
        "https://cache.nixos.org/"
      ];
      trusted-public-keys = [
        # "hyprland.cachix.org-1:a7pgxzMz7+chwVL3/pzj6jIBMioiJM7ypFP8PwtkuGc="
        "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
      ];
    };
    gc = {
      automatic = true;
      frequency = "weekly";
      # Keep the last 60 days of generations
      options = "--delete-older-than 60d";
    };
  };
}
