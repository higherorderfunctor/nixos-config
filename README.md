# nixos-config

## Helpful Commands

```sh
# update lock file
nix flake update

# refresh flake from remote (e.g. making edits while testing install from ISO)
nix flake update --refresh github:higherorderfunctor/nixos-config?ref=fix/ssh-key-permissions

# show outputs
nix flake show

# check for errors in outputs
nix flake check

# inspect outputs
nix repl
:lf .

outputs.<tab>
````

## Building Live CD Installer ISO

Build a bootable NixOS Live CD Installer ISO with SSH enabled and public key preloaded.

```sh
# minimal
nix build .#nixosConfigurations.live-cd-minimal-x86_64-linux.config.system.build.isoImage

# graphical
nix build .#nixosConfigurations.live-cd-graphical-x86_64-linux.config.system.build.isoImage
```

## Installing

Example install of the `#vm` hosts, but can be any host in `./hosts`.

```sh
##
# REMOTE: get target SSH address after booting the live CD

ip --brief addr show


##
# HOST: SSH into target

# virtualbox
REMOTE=root@localhost
PORT=2522
# real host
REMOTE=root@192.168.9.130
PORT=22

ssh -p "$PORT" "$REMOTE"


##
# REMOTE (ssh): partition drive(s)

# check LBA format
nix run nixpkgs#nvme-cli -- id-ns /dev/nvme0n1 -H | grep "^LBA Format"

# update to best LBA format (destructive!)
nix run nixpkgs#nvme-cli -- format /dev/nvme0n1 --force --lbaf <BEST>

# partition drive

BRANCH=fix/ssh-key-permissions
TARGET=beelink-ser7

nix run github:nix-community/disko -- --mode disko --flake  \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$TARGET"

# TODO:

nix run github:nix-community/disko -- --mode mount --flake  \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$TARGET"

# check disks
fdisk -l
lsblk -l
btrfs subvolume list /mnt
findmnt -nt btrfs


##
# REMOTE (ssh): build the config

git clone -b "$BRANCH" https://github.com/higherorderfunctor/nixos-config.git \
  /mnt/etc/nixos

nixos-generate-config --root /mnt --show-hardware-config

# copy wanted configs into hosts/vm/hardware-configuration.nix

# virtualbox
REMOTE=root@localhost
PORT=2522
# real host
REMOTE=root@192.168.9.130
PORT=22

# copy secrets key for sops

scp -P "$PORT" -r ~/.ssh/id_ed25519 "$REMOTE":/mnt/etc/nixos/home/caubut/id_ed25519


##
# REMOTE (ssh): run the installation

nixos-install --no-root-passwd --flake "/mnt/etc/nixos#$TARGET"
````

## Updating

```sh
nixos-rebuild --flake github:higherorderfunctor/nixos-config?ref=fix/ssh-key-permissions switch
```

## Managing Secrets

```sh
# generate key pair if needed
ssh-keygen -t ed25519

# derive a private key from an SSH private key
mkdir -p ~/.config/sops/age
nix-shell -p ssh-to-age --run "ssh-to-age -private-key -i ~/.ssh/id_ed25519 > ~/.config/sops/age/keys.txt"

# derive a public key from an SSH public key
nix-shell -p ssh-to-age --run 'cat ~/.ssh/id_ed25519.pub | ssh-to-age'

# generate password hashes to store
mkpasswd --method=SHA-512 --stdin

# create/edit a secrets file
nix-shell -p sops --run "sops hosts/common/secrets.yaml"
```

## Linters, Formatters, and LSPs

### statix (linter)

nvim: `nvim-lint`

```sh
nix profile install github:NixOS/nixpkgs#statix
statix check flake.nix
```

### deadnix (linter)

nvim: `none-ls`

```sh
nix profile install github:astro/deadnix#
deadnix flake.nix
```

### nil (lsp)

nvim: `mason`, `nvim-lspconfig`

```sh
nix profile install github:oxalica/nil#
```

### nixd (lsp)

nvim: `neovim/nvim-lspconfig`

```sh
nix profile install github:nix-community/nixd#
```
