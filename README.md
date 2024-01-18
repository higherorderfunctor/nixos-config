# nixos-config

## Prepare Secrets

In this setup, secrets are managed with sops.  Users and hosts will use different
keys to encrypt/decrypt secrets.

### Generate User Keys

To generate a key for the current user on an existing host (NixOS or just Nix),
generate a key-pair without a password.  Do not lose the private key!  It must
be manually copied later.  You may have an existing one used for SSH that can be
reused for sops.

```sh
# for a new key pair
ssh-keygen -t ed25519 -f home/caubut/secrets

# for an existing key pair
cp ~/.ssh/id_ed25519.pub home/caubut/secrets
```

### Generate Host Keys

Same steps as above, just for hosts to decrypt secrets.  Again, no password.  This
key will also be the host's SSH key.

```sh
# generate key pair
ssh-keygen -t ed25519 -f hosts/<HOST>/secrets/ssh_host_ed25519_key

# example
ssh-keygen -t ed25519 -f hosts/beelink-ser7/secrets/ssh_host_ed25519_key
ssh-keygen -t ed25519 -f hosts/vm/secrets/ssh_host_ed25519_key
```

### Setup SOPS

Add all public keys to `sops.yaml` under users or hosts with an age key.

```sh
# derive a public key from an SSH public key
nix-shell -p ssh-to-age --run 'cat home/<USER>/secrets/id_ed25519.pub | ssh-to-age'

# example
nix-shell -p ssh-to-age --run 'cat home/caubut/secrets/id_ed25519.pub | ssh-to-age'
nix-shell -p ssh-to-age --run \
  'cat hosts/beelink-ser7/secrets/ssh_host_ed25519_key.pub | ssh-to-age'
nix-shell -p ssh-to-age --run 'cat hosts/vm/secrets/ssh_host_ed25519_key.pub | ssh-to-age'
```

Secrets are stored in either `home/<USER>/secrets/secrets.yaml`, `hosts/<HOST>/secrets/secrets.yaml`,
or `hosts/common/secrets/<SCOPE>.yaml`.  Fill out the matrix in `sops.yaml` for which
users and hosts should have access to which secrets.

To start making secrets, on the current host, configure age.  This enables
decryption of any existing secrets.

```sh
# derive an age private key from an SSH private key
mkdir -p ~/.config/sops/age
nix-shell -p ssh-to-age --run \
  "ssh-to-age -private-key -i ~/.ssh/id_ed25519 > \
  ~/.config/sops/age/keys.txt"
```

Edit the secrets which can be decrypted per the `.sops.yaml` matrix.

```sh
nix-shell -p sops --run "sops home/<USER>/secrets/secrets.yaml"
nix-shell -p sops --run "sops hosts/<HOST>/secrets/secrets.yaml"
nix-shell -p sops --run "sops hosts/common/secrets/<SCOPE>.yaml"

# example
nix-shell -p sops --run "sops home/caubut/secrets/secrets.yaml"
nix-shell -p sops --run "sops hosts/beelink-ser7/secrets/secrets.yaml"
nix-shell -p sops --run "sops hosts/vm/secrets/secrets.yaml"
nix-shell -p sops --run "sops hosts/common/secrets/wireless.yaml"
# TODO: update command: nix run nixpkgs#sops -- hosts/common/secrets/wireless.yaml
```

User password hashes can be generated with the following.

```sh
nix-shell -p mkpasswd --run 'mkpasswd --method=SHA-512 --stdin'
```

## Build a Live CD Installer ISO

Build a bootable NixOS Live CD Installer ISO with SSH enabled and the user's public
key preloaded.

See `hosts/common/optional/openssh.nix` for adding the key.

```sh
# minimal
nix build .#nixosConfigurations.live-cd-minimal-x86_64-linux.config.system.build.isoImage

# graphical
nix build .#nixosConfigurations.live-cd-graphical-x86_64-linux.config.system.build.isoImage
```

## Install

Boot from the NixOS Live CD Installer ISO.

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

BRANCH=fix/user-permissions
NIXOS_HOST=vm

# partition disk(s)
nix run github:nix-community/disko -- --mode disko --flake  \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST"

# check disk(s)
fdisk -l
lsblk -l
btrfs subvolume list /mnt
findmnt -nt btrfs


##
# REMOTE (ssh): build the config

# generate hardware config
nixos-generate-config --root /mnt --show-hardware-config

# copy wanted configs into hosts/$NIXOS_HOST/hardware-configuration.nix

# commit and push any changes


##
# HOST: copy host specific private key to sops

# restore the host specific private key

# example: copy from host secrets
nix-shell -p sops --run "sops hosts/beelink-ser7/secrets/secrets.yaml"
vim hosts/beelink-ser7/secrets/ssh_host_ed25519_key
chmod 600 hosts/beelink-ser7/secrets/ssh_host_ed25519_key

# scp key to persistent storage for impermanence

# virtualbox
REMOTE=root@localhost
PORT=2522
# real host
REMOTE=root@192.168.9.130
PORT=22

NIXOS_HOST=beelink-ser7

ssh -p "$PORT" "$REMOTE" "mkdir -p /mnt/persist/etc/ssh/"
scp -P "$PORT" -r hosts/$NIXOS_HOST/secrets/ssh_host_ed25519_key \
  "$REMOTE":/mnt/persist/etc/ssh/ssh_host_ed25519_key


##
# REMOTE (ssh): run the installation

BRANCH=fix/user-permissions
NIXOS_HOST=beelink-ser7

# update and check the flake if hardware modifications made
nix flake check --refresh "github:higherorderfunctor/nixos-config?ref=$BRANCH"

# install nixos
nixos-install --no-root-passwd --flake  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST"

# reboot
reboot
````

## Updating

### Updating on the Host

```sh
BRANCH=fix/user-permissions

# update and check the flake if hardware modifications made
nix flake check --refresh "github:higherorderfunctor/nixos-config?ref=$BRANCH"

# rebuild nixos
sudo nixos-rebuild --refresh --flake \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST" switch

# rebuild nixos with full stack trace
sudo nixos-rebuild --refresh --flake \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST" switch \
  --show-trace --option eval-cache false
```

### Updating from a Live CD

```sh
BRANCH=fix/user-permissions
NIXOS_HOST=vm

# mount disk(s)
nix run github:nix-community/disko -- --mode mount --flake  \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST"

# update and check the flake
nix flake check --refresh "github:higherorderfunctor/nixos-config?ref=$BRANCH"

# normally cleared on boot and restored by impermanence
rm /mnt/etc/machine-id
rm /mnt/etc/ssh/ssh_host_ed25519_key

# install nixos
nixos-install --no-root-passwd --flake "github:higherorderfunctor/nixos-config?ref=$BRANCH#$NIXOS_HOST"
```

## Helpful Commands

```sh
# update lock file
nix flake update

# show outputs
nix flake show

# check for errors in outputs
nix flake check

# inspect outputs
nix repl
:lf .

outputs.<tab>

# view dependencies
nix flake metadata

# list installed packages
ls /nix/store/

# https://nixos.org/manual/nix/stable/command-ref/nix-store/query.html

# list activate installed packages
nix-store -q --requisites /run/current-system

# show dependency tree
nix-store -q --tree /run/current-system

# see which build is keeping a dependency
nix-store -q --roots /nix/store/...

# show generations
nix profile history --profile /nix/var/nix/profiles/system

# purge old generations
sudo nix profile wipe-history --profile /nix/var/nix/profiles/system

# clean the store
nix store gc

# fix build after manual tinkering
sudo nix-store --verify --check-contents --repair
````

## Home Manager

```ssh
# show persistent directories
findmnt -nt fuse
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

## Other

```sh
journalctl --user -b -x
journalctl --user -b -x -p3
journalctl -b -x -p3
fwupdmgr refresh
fwupdmgr get-devices
fwupdmgr get-updates
modinfo iwlwifi
sudo lspci -v | less
````
