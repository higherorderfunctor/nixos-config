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

# linter error TODO: fix
nix flake archive --extra-experimental-features 'nix-command flakes'


nixos-generate-config --root /mnt
nixos-generate-config --root .
--no-write-lock-file for updates

nixos-rebuild --extra-experimental-features 'nix-command flakes' --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config switch
# WARN: may have to target flake instead of use switch? "." see Misterio77's config
```

## VM Testing

```sh
# update the flake from git if testing modifications
sudo nix flake update --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config

sudo nix run --extra-experimental-features 'nix-command flakes' github:nix-community/disko -- --mode disko --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm

# run the installation
sudo nixos-install --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm
````

### Testing Modifications

```sh
# host
nix flake update --extra-experimental-features 'nix-command flakes'
git commit -am 'message'
git push

# vm
nix flake update --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config
```

## Linters, Formatters, and LSPs

### nix-repl

nvim: no, manual inspection of config.  Use <tab> to walk config to inspect.

```sh
nix repl --extra-experimental-features 'nix-command flakes'
:lf .
nixosConfigurations.beelink-ser7
```

### statix (linter)

nvim: yes via `nvim-lint`.

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:NixOS/nixpkgs#statix
statix check flake.nix
```

### deadnix (linter)

nvim: yes, using `none-ls`.

```sh
nix profile install --extra-experimental-features 'nix-command flakes' github:astro/deadnix#
deadnix flake.nix
```

### nil (lsp)

nvim: yes, managed via `mason` and configured automatically via `nvim-lspconfig`.

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:oxalica/nil#
```

### nixd (lsp)

nvim: yes, using `neovim/nvim-lspconfig`.

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:nix-community/nixd#
```
