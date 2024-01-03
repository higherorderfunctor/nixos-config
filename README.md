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
# TARGET: get target SSH address after booting the live CD

ip --brief addr show

##
# HOST: SSH into target

# virtualbox
TARGET=root@localhost
PORT=2522
# real host
TARGET=root@<TARGET>
PORT=22

ssh -p "$PORT" "$TARGET"

##
# TARGET (ssh): partition drive(s)

# check LBA format
nix run nixpkgs#nvme-cli -- id-ns /dev/nvme0n1 -H | grep "^LBA Format"

# update to best LBA format (destructive!)
nix run nixpkgs#nvme-cli -- format /dev/nvme0n1 --force --lbaf <BEST>

# partition drive
nix run github:nix-community/disko -- --mode disko --refresh --flake  \
  github:higherorderfunctor/nixos-config?ref=fix/ssh-key-permissions#vm

# take an empty snapshot of root
mkdir /btrfs
mount -t btrfs /dev/mapper/cryptlvm-root /btrfs
btrfs subvolume snapshot -r /btrfs /btrfs/root-blank
umount /mnt/btrfs

# TODO:
cryptsetup luksOpen /dev/nvme0n1p1 /a

[root@nixos:~]# lsblk -l
NAME          MAJ:MIN RM  SIZE RO TYPE  MOUNTPOINTS
loop0           7:0    0  1.1G  1 loop  /nix/.ro-store
sr0            11:0    1  1.1G  0 rom   /iso
cryptlvm      254:0    0    6G  0 crypt
cryptlvm-root 254:1    0    6G  0 lvm   /mnt/persist
                                        /mnt/nix
                                        /mnt/home
                                        /mnt
nvme0n1       259:0    0    8G  0 disk
nvme0n1p1     259:2    0    2G  0 part  /mnt/boot
nvme0n1p2     259:3    0    6G  0 part

# check disks
fdisk -l
lsblk -l
btrfs subvolume list /mnt
findmnt -nt btrfs

##
# TARGET (ssh): generate hardware config

nixos-generate-config --root /mnt --show-hardware-config

# copy wanted configs into hosts/vm/hardware-configuration.nix

##
# HOST: copy key to decrypt secrets to the target

# virtualbox
TARGET=root@localhost
PORT=2522
# real host
TARGET=root@<TARGET>
PORT=22

ssh -p "$PORT" "$TARGET" "mkdir -p /mnt/etc/ssh"
scp -P "$PORT" -r ~/.ssh/id_ed25519 "$TARGET":/mnt/etc/ssh/ssh_host_ed25519_key

##
# TARGET (ssh): run the installation

cd /mnt
nixos-install --no-root-passwd --flake github:higherorderfunctor/nixos-config?ref=fix/ssh-key-permissions#vm
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
