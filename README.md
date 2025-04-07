# nixos-config

## Prepare Secrets

In this setup, secrets for users and hosts are managed with
[SOPS](https://github.com/Mic92/sops-nix).

### Generate User Keys

To generate a key-pair for the current user on an existing host, generate a
key-pair without a password.  Do not lose the private key!  It must be
manually copied later.  You may have an existing one used for SSH that can be
reused for SOPS.

```sh
mkdir -p home/<USER>/secrets

# for a new key pair
ssh-keygen -t ed25519 -f home/<USER>/secrets

# for an existing key pair
cp ~/.ssh/id_ed25519.pub home/<USER>/secrets
```

### Generate Host Keys

To generate a key-pair for the new host, generate a key-pair without a password.
Do not lose the private key!  It must be manually copied later.

```sh
mkdir -p hosts/<HOST>/secrets

# generate key pair
ssh-keygen -t ed25519 -f hosts/<HOST>/secrets/ssh_host_ed25519_key
```

### Setup SOPS

Convert all keys to age keys to use with SOPS.

```sh
# derive user public age keys from SSH public keys
cat home/<USER>/secrets/id_ed25519.pub | nix run nixpkgs#ssh-to-age

# derive host public age keys from SSH public keys
cat hosts/<HOST>/secrets/ssh_host_ed25519_key.pub | nix run nixpkgs#ssh-to-age

mkdir -p ~/.config/sops/age

# derive user private age keys from SSH private keys to decrypt secrets locally
nix run nixpkgs#ssh-to-age -private-key -i ~/.ssh/id_ed25519 > \
  ~/.config/sops/age/keys.txt"
```

Add any new public keys to `sops.yaml` and fill out the matrix in `sops.yaml`
to set which users and hosts should have access to which secrets.

Generate a user password hash for users on any new hosts.

```sh
nix run nixpkgs#mkpasswd -- --method=SHA-512 --stdin
```

Add user password hashes to their secrets file.

```sh
EDITOR=vi nix run nixpkgs#sops home/<USER>/secrets/secrets.yaml
```

Add host private keys to `hosts/<HOST>/secrets/secrets.yaml`.

```sh
EDITOR=vi nix run nixpkgs#sops hosts/<HOST>/secrets/secrets.yaml

# delete any SSH private keys from the file system
rm hosts/<HOST>/secrets/ssh_host_ed25519_key
```

Commit the secrets before attempting to install.

## Build a Live CD Installer ISO

Build a bootable NixOS Live CD Installer ISO with SSH enabled and the user's public
key preloaded.

```sh
# minimal
nix build .#nixosConfigurations.live-cd-minimal-x86_64-linux.config.system.build.isoImage

# graphical
nix build .#nixosConfigurations.live-cd-graphical-x86_64-linux.config.system.build.isoImage

# find the name of the boot media (e.g., usb thumb drive)
lsblk -o NAME,SIZE,VENDOR,MODEL,SERIAL,MOUNTPOINT,TRAN | grep -i usb

# copy the ISO to the boot media
sudo dd status=progress \
        if=result/iso/nixos-gnome-25.05.20250319.a84ebe2-x86_64-linux.iso \
        of=/dev/sda \
        bs=128k

# flush writes
sync
```

## Installation

Boot from the NixOS Live CD Installer ISO.

*REMOTE HOST:* Get target SSH address after booting the live CD.

```sh
ip --brief addr show
```

*LOCAL:* SSH into target.

```sh
HOST=root@x.x.x.x

ssh "$HOST"
```

*REMOTE HOST (via ssh):* Partition drive(s).

```sh
# check LBA format
nix run nixpkgs#nvme-cli -- id-ns /dev/nvme0n1 -H | grep "^LBA Format"

# update to best LBA format (destructive!)
nix run nixpkgs#nvme-cli -- format /dev/nvme0n1 --force --lbaf <BEST>

BRANCH=<BRANCH>
HOSTNAME=<HOST>

# partition disk(s)
nix run github:nix-community/disko -- --mode disko --flake  \
  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$HOSTNAME"

# check disk(s)
fdisk -l
lsblk -l
btrfs subvolume list /mnt
findmnt -nt btrfs
findmnt -n
```

*REMOTE HOST (via ssh):* Build the hardware config.

```sh
# generate hardware config
nixos-generate-config --root /mnt --show-hardware-config

# copy wanted configs into hosts/$NIXOS_HOST/hardware-configuration.nix

# commit and push any changes
```

*LOCAL:* Copy host specific private key to SOPS.

```sh
# scp key to persistent storage for impermanence

HOST=root@

ssh "$HOST" "mkdir -p /mnt/persist/etc/ssh/"

# TODO from sops/set 600
scp -r ~/.ssh/<HOST>_ed25519_key "$HOST":/mnt/persist/etc/ssh/ssh_host_ed25519_key
```

*REMOTE (ssh):* Run the installation.

```sh
BRANCH=
HOSTNAME=

# update and check the flake if hardware modifications made
nix flake check --refresh "github:higherorderfunctor/nixos-config?ref=$BRANCH"

# install nixos
nixos-install --no-root-passwd --flake  "github:higherorderfunctor/nixos-config?ref=$BRANCH#$HOSTNAME"

# reboot
reboot
````
