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

--no-write-lock-file for updates
```

nixos-rebuild --extra-experimental-features 'nix-command flakes' --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config switch

nix run --extra-experimental-features 'nix-command flakes' nixpkgs#statix -- help

nix profile install  --extra-experimental-features 'nix-command flakes' github:nerdypepper/statix
nix profile install  --extra-experimental-features 'nix-command flakes' github:siraben/nix-lint

nix-lint is manual


# TODO deadnix

nix profile install --extra-experimental-features 'nix-command flakes' github:nix-community/nixd
