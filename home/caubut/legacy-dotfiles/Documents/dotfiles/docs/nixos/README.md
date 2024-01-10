cd ./Documents/dotfiles/docs/nixos

nix-build '<nixpkgs/nixos>' -A config.system.build.isoImage -I nixos-config=iso.nix
