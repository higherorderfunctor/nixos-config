# nixos-config

```sh
sudo nix run --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config#install

nix flake update --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config

nix flake show --extra-experimental-features 'nix-command flakes' github:higherorderfunctor/nixos-config?ref=feat/disk-config

nix flake show
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

## Building Installer ISO

Build a bootable NixOS ISO with SSH enabled and public key preloaded.

```sh
nix build .#nixosConfigurations.live-cd-x86_64.config.system.build.isoImage
```

## Installing

```sh
# using `vm` as the host, but can be anything in `./hosts`

##
# TARGET: get target SSH address after booting the live CD

ip --brief addr show

##
# HOST: SSH into target

ssh root@<TARGET>

##
# TARGET (ssh): partition drive(s)

# check LBA format
sudo nix run nixpkgs#nvme-cli -- id-ns /dev/nvme0n1 -H
nix-shell -p nvme-cli --run "nvme id-ns /dev/nvme0n1 -H" | grep "^LBA Format"

# update to best LBA format (destructive!)
nix-shell -p nvme-cli --run "nvme format /dev/nvme0n1 --force --lbaf <BEST>"

# partition drive
nix-shell -p disko --run \
  "disko --mode disko --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm"
sudo nix run github:nix-community/disko -- --mode disko --flake \
  github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm

# local clone
sudo nix run \
  --extra-experimental-features 'nix-command flakes' \
  github:nix-community/disko -- --mode disko --flake \
  $PWD#vm

# check disks
sudo fdisk -l
lsblk -l

##
# generate hardware config

sudo nixos-generate-config --root /mnt --show-hardware-config

# copy anything wanted into hosts/vm/hardware-configuration.nix

##
# update flake with any changes

nix flake update --extra-experimental-features 'nix-command flakes'
nix flake check --extra-experimental-features 'nix-command flakes'
git commit -am 'message'
git push

##
# run the installation

sudo nixos-install --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm
````

## Updating

```sh
nixos-rebuild --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config switch
```

## Secrets Management

```sh
# derive a private key from an SSH private key
nix-shell -p ssh-to-age --run "ssh-to-age -private-key -i ~/.ssh/id_ed25519 > ~/.config/sops/age/keys.txt"

# derive a public key from an SSH public key
nix-shell -p ssh-to-age --run 'cat ~/.ssh/id_ed25519.pub | ssh-to-age'

# create/edit a secrets file
nix-shell -p sops --run "sops hosts/common/secrets.yaml"
```


## Linters, Formatters, and LSPs

### nix-repl

```sh
nix repl --extra-experimental-features 'nix-command flakes'
:lf .
```

### statix (linter)

nvim: `nvim-lint`

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:NixOS/nixpkgs#statix
statix check flake.nix
```

### deadnix (linter)

nvim: `none-ls`

```sh
nix profile install --extra-experimental-features 'nix-command flakes' github:astro/deadnix#
deadnix flake.nix
```

### nil (lsp)

nvim: `mason`, `nvim-lspconfig`

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:oxalica/nil#
```

### nixd (lsp)

nvim: `neovim/nvim-lspconfig`

```sh
nix profile install  --extra-experimental-features 'nix-command flakes' github:nix-community/nixd#
```
