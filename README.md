# nixos-config

```sh
sudo nix run --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config#install

nix flake update --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config

nix flake show --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config

nix flake show --extra-experimental-features 'nix-command flakes' .
nix run --extra-experimental-features 'nix-command flakes' .#install

# update lock
nix flake update --extra-experimental-features 'nix-command flakes'

# check config
nix flake check --extra-experimental-features 'nix-command flakes'
```

nixos-rebuild --extra-experimental-features 'nix-command flakes' --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config switch
