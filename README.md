# nixos-config

```sh
sudo nix run --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=boot-config#install

nix flake update --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=boot-config#install

nix flake show --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=boot-config

nix flake show --extra-experimental-features 'nix-command flakes' .
nix run --extra-experimental-features 'nix-command flakes' .#install
```

