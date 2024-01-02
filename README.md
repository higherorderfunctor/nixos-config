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

nixos-generate-config --root /mnt --show-hardware-config

# copy wanted configs into hosts/vm/hardware-configuration.nix

##
# HOST: copy key to decrypt secrets to the target

# TODO: verify root
rsync -ravs --mkpath --progress --chown=root:root ~/.ssh/id_ed25519 root@<TARGET>:/mnt/etc/ssh/ssh_host_ed25519_key

##
# TARGET (ssh): run the installation

cd /mnt
nixos-install --no-root-passwd --flake  github:higherorderfunctor/nixos-config?ref=feat/disk-config#vm
````

## Updating

```sh
nixos-rebuild --flake github:higherorderfunctor/nixos-config?ref=feat/disk-config switch
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
