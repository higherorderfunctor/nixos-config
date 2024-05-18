# nixos-config

## Preparing Secrets

In this setup, secrets are managed with sops.  Users and hosts will use different
keys to encrypt/decrypt secrets.

### Generating Keys

Generate needed key-pairs without a password.

```sh
# users
ssh-keygen -t ed25519 -f ~/.ssh/personal_ed25519_key
ssh-keygen -t ed25519 -f ~/.ssh/professional_ed25519_key

# hosts
ssh-keygen -t ed25519 -f ~/.ssh/beelink_ser7_ed25519_key
ssh-keygen -t ed25519 -f ~/.ssh/vm_ed25519_key
```

Copy the public keys into the repo.

```sh
# users
cp ~/.ssh/personal_ed25519_key.pub home/caubut/secrets/personal_ed25519_key.pub
cp ~/.ssh/professional_ed25519_key.pub home/caubut/secrets/professional_ed25519_key.pub

# hosts
cp ~/.ssh/beelink_ser7_ed25519_key.pub hosts/beelink-ser7/secrets/ssh_host_ed25519_key.pub
cp ~/.ssh/vm_ed25519_key.pub hosts/vm/secrets/ssh_host_ed25519_key.pub
```

### Setup SOPS

Add public keys to `sops.yaml` under users or hosts with an age key.  The keys
can unlock the sops files.

```sh
# derive a public key from an SSH public key
cat home/caubut/secrets/personal_ed25519_key.pub | ssh-to-age
cat hosts/beelink-ser7/secrets/ssh_host_ed25519_key.pub | ssh-to-age
cat hosts/vm/secrets/ssh_host_ed25519_key.pub | ssh-to-age
```

Secrets are stored in either `home/<USER>/secrets/secrets.yaml`, `hosts/<HOST>/secrets/secrets.yaml`,
or `hosts/common/secrets/<SCOPE>_secrets.yaml`.  Fill out the matrix in `.sops.yaml`
for which users and hosts should have access to which secrets.

To start making secrets, on the current host, configure age.  This enables
decryption of any existing secrets.

```sh
# derive an age private key from an SSH private key
mkdir -p ~/.config/sops/age
ssh-to-age -private-key -i ~/.ssh/personal_ed25519_key > ~/.config/sops/age/keys.txt
```

Edit the secrets which can be decrypted per the `.sops.yaml` matrix.

```sh
# disable temp files and plugins that might leak
set shada?
set undofile?
set backup?
set writebackup?
set viminfo?
EDITOR="nvim -u NONE -i NONE -n --cmd 'set noundofile noswapfile nobackup nowritebackup viminfo=\"\"'"

sops home/caubut/secrets/secrets.yaml
sops hosts/beelink-ser7/secrets/secrets.yaml
sops hosts/vm/secrets/secrets.yaml
sops hosts/common/secrets/wireless.yaml

sops hosts/beelink-ser7/secrets/gluetun.env
sops hosts/beelink-ser7/secrets/wireguard.ini
```

User password hashes can be generated with the following.

```sh
nix run nixpkgs#mkpasswd -- --method=SHA-512 --stdin
```

```sh
# https://github.com/nix-community/home-manager/issues/4692
sh <(curl -L https://releases.nixos.org/nix/nix-2.18.1/install) --daemon

# update
nix flake update

nix run .#homeConfigurations.caubut@precision-7760.activationPackage -- build . switch
nix run .#homeConfigurations.caubut@z690-ud-ddr4.activationPackage -- build . switch

# list generations
home-manager generations

# clean up
home-manager remove-generations ID
home-manager expire-generations TIMESTAMP

./scripts/remove-generations

nix profile history
nix profile wipe-history
nix store gc

# see why a package is a dependency
nix-store -q --tree ~/.nix-profile
nix why-depends .#homeConfigurations.caubut@precision-7760.activationPackage /nix/store/...
nix why-depends .#homeConfigurations.caubut@z690-ud-ddr4.activationPackage /nix/store/...
```

## Setup

### Secure System

```console
git clone --bare git@github.com:higherorderfunctor/dotfiles.git $HOME/.dotfiles
alias dotfiles='/usr/bin/git --git-dir=$HOME/.dotfiles/ --work-tree=$HOME'
dotfiles checkout main

.local/bin/dotfiles-update

# restart shell
```

### Insecure System

```console
git clone --bare https://github.com/higherorderfunctor/dotfiles.git $HOME/.dotfiles
alias dotfiles='/usr/bin/git --git-dir=$HOME/.dotfiles/ --work-tree=$HOME'
dotfiles checkout main

.local/bin/dotfiles-update --no-secure

# restart shell
```

## Update

```console
# secure system
dotfiles-update

# insecure system
dotfiles-update --no-secure

# update environment
source "$HOME/.zshrc" && rehash
```

## Backup

Backup management is done with the custom `vault` command.  It is a wrapper around `rclone` with an encrypted `rclone.conf` for remotes of type `crypt`.  Credentials are managed through `bw`, the Bitwarden CLI.  The Bitwarden database is updated once an hour automatically when a `vault` command is run.  The Bitwarden item for `rclone` is set with the `BW_RCLONE_CONF` environment variable (default: `rclone - config`).

The Bitwarden item also is used to store the latest `rclone.conf`.  During an update of the database, if `rclone.conf` is newer in Bitwarden, it syncs locally.  A backup of the local version is created locally before syncing at `~/.config/rclone/rclone.local.conf.bk`.

The automations in the wrapper are intended to work with `rclone` remotes of type `crypt` named `crypt-<local|remote>-<VAULT>`.

Parallelism is automatically set to `2 * $(nproc --all)`.

### Unlock

Prompts for Bitwarden credentials and starts a new shell.

```console
vault unlock
```

### Lock

Destroys the Bitwarden session, unmounts any mounted file systems if able, and cleans up the VFS cache.

```console
exit
```

### Configure

Launches `rclone config`.  If the config is updated, it creates a backup of the remote `rclone.conf` called `rclone.remote.conf.bk` both locally at `~/.config/rclone/rclone.remote.conf.bk` and on the Bitwarden item.

```console
vault config
```

### Mount Vault

Mounts a vault using FuseFS.

```console
# local vault
vault mount local <VAULT>

# remote vault
vault mount remote <VAULT> --vfs-cache-mode full
```

If mounted using daemon mode, `xdg-open` will open the mount point.

```console
# local vault
vault mount local <VAULT> --daemon

# remote vault
vault mount remote <VAULT> --daemon --vfs-cache-mode full
```

Unmounting can be performed by killing the process (non-daemon), manually (daemon), or exiting the unlocked shell.

```console
vault unmount <local|remote> <VAULT>
```

Unmounting can also be forced.

```console
vault unmount <local|remote> <VAULT> -z
```

### Check Differences

Check for differences between local and remote for a given vault.  This is slower compared to using `--dry-run` with `copy` or `sync` (see below).

```console
vault check local <VAULT>
```

### Sync Files

Sync files between local and remote.  This script does not currently handle three-way merges so tread carefully.

Copy new or updated files between local and remote.

```console
# local to remote
vault copy local <VAULT>

# remote to local
vault copy remote <VAULT>
```

Copy new or updated files between local and remote.  Deletes any files not in the source vault.

```console
# local to remote
vault sync local <VAULT>

# remote to local
vault sync remote <VAULT>
```

### Other

These commands/flags are not well tested yet.

```console
# proton 2fa flag
--protondrive-2fa=

# proton replace failed upload
--protondrive-replace-existing-draft=true

# whole disk backup
sudo dd if=/dev/<DISK> bs=128K status=progress |
  gzip -c > ~/.local/share/rclone/mnt/<MOUNT>/<PATH/TO/IMAGE>.gz
```

## Recoll

### Example Config

```console
# ~/.config/recoll/work/recoll.conf
topdirs = ~/.local/share/rclone/mnt/Work
cachedir = ~/.local/share/rclone/mnt/Work/.recoll
skippedNames = ~/.local/share/rclone/mnt/Work/.recoll
indexstemminglanguages = english
```

### Running

```console
vault mount local work --vfs-cache-mode=full -d
recollindex -c .config/recoll/work
recollq -c .config/recoll/work <QUERY>
vault unmount local work
rm -rf ~/.cache/rclone/vfs/crypt-local-work
```

## Secure File Backup

```console
https://askubuntu.com/questions/907425/how-do-i-back-up-and-restore-passwords-and-keys
bw unlock
vault mount local <VAULT> --vfs-cache-mode full --daemon
mkdir -p <VAULT_MOUNT_POINT>/Backups/Home/$(hostname)
cp -R ~/.local/share/keyrings <VAULT_MOUNT_POINT>/Backups/Home/$(hostname)
cp -R ~/.ssh <VAULT_MOUNT_POINT>/Backups/Home/$(hostname)
cp -R ~/.gnupg <VAULT_MOUNT_POINT>/Backups/Home/$(hostname)
vault unmount local <VAULT>
```

# NodeJS

Download the latest LTS or Current version of [nodejs](https://nodejs.org/en/download/current).

```console
curl -fsSL https://get.pnpm.io/install.sh | sh -
pnpm env use --global 20
pnpm exec node --version
```

# Extra

```
https://www.nerdfonts.com/font-downloads
monaspice



dbus-send --print-reply --dest=org.freedesktop.DBus  /org/freedesktop/DBus org.freedesktop.DBus.ListNames
```

```sh
cat $XDG_RUNTIME_DIR/hypr/$(ls -t $XDG_RUNTIME_DIR/hypr/ | head -n 1)/hyprland.log
cat $XDG_RUNTIME_DIR/hypr/$(ls -t $XDG_RUNTIME_DIR/hypr/ | head -n 2 | tail -n 1)/hyprland.log
journalctl -b -p3
```
