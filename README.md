# nixos-config


## Helpful Commands

```sh
# update lock file
nix flake update

# refresh flake from remote (e.g. making edits while testing install from ISO)
nix flake update --refresh github:higherorderfunctor/nixos-config?ref=feat/disk-config

# show outputs
nix flake show

# check for errors in outputs
nix flake check

# inspect outputs
nix repl
:lf .

outputs...
````

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
nix run nixpkgs#nvme-cli -- id-ns /dev/nvme0n1 -H | grep "^LBA Format"

# update to best LBA format (destructive!)
nix run nixpkgs#nvme-cli -- format /dev/nvme0n1 --force --lbaf <BEST>

# partition drive
nix run github:nix-community/disko -- --mode disko --refresh --flake  \
  github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm

# check disks
sudo fdisk -l
lsblk -l

##
# TARGET (ssh): generate hardware config

sudo nixos-generate-config --root /mnt --show-hardware-config

# copy anything wanted into hosts/vm/hardware-configuration.nix

##
# TARGET (ssh): run the installation

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
