{lib, ...}: {
  nix = {
    settings = {
      trusted-users = ["root" "@wheel"];
      auto-optimise-store = lib.mkDefault true;
      experimental-features = ["nix-command" "flakes" "repl-flake"];
    };
    gc = {
      automatic = true;
      dates = "weekly";
      # Keep the last 60 days of generations
      options = "--delete-older-than 60d";
    };
  };
}
