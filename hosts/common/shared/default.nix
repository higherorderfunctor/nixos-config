{lib, ...}: let
  substituters = [
    "https://cache.nixos.org/"
    "https://nix-community.cachix.org"
    "https://hyprland.cachix.org"
    "https://wezterm.cachix.org"
  ];
in {
  nix = {
    settings = {
      cores = lib.mkForce 4;
      max-jobs = lib.mkForce 1;
      trusted-users = ["root" "caubut" "@wheel"];
      auto-optimise-store = lib.mkDefault true;
      experimental-features = ["nix-command" "flakes"];
      # nixos
      inherit substituters;
      # home manager
      trusted-substituters = substituters;
      trusted-public-keys = [
        "cache.nixos.org-1:6NCHdD59X431o0gWypbMrAURkbJ16ZPMQFGspcDShjY="
        "hyprland.cachix.org-1:a7pgxzMz7+chwVL3/pzj6jIBMioiJM7ypFP8PwtkuGc="
        "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
        "wezterm.cachix.org-1:kAbhjYUC9qvblTE+s7S+kl5XM1zVa4skO+E/1IDWdH0="
      ];
    };
    gc = {
      automatic = true;
      # dates = "weekly";
      # Keep the last 60 days of generations
      options = "--delete-older-than 60d";
    };
  };
}
