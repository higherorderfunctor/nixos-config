# Dotfiles

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

# Ansible

## Activating

```console
. "$HOME/.local/share/ansible/bin/activate"
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
curl -LO https://github.com/BurntSushi/ripgrep/releases/download/14.0.3/ripgrep_14.0.3-1_amd64.deb
sudo dpkg -i ripgrep_14.0.3-1_amd64.deb

https://www.nerdfonts.com/font-downloads
monaspice


-$ curl -R -O http://www.lua.org/ftp/lua-5.3.5.tar.gz
-$ tar -zxf lua-5.3.5.tar.gz
-$ cd lua-5.3.5
-$ make linux test
-$ sudo make install
cd ..
curl -R -O https://luarocks.github.io/luarocks/releases/luarocks-3.9.2.tar.gz
tar -zxf luarocks-3.9.2.tar.gz
cd luarocks-3.9.2
./configure --with-lua-include=/usr/local/include
make
sudo make install
cd ..
rm -rf lua*



LAZYGIT_VERSION=$(curl -s "https://api.github.com/repos/jesseduffield/lazygit/releases/latest" | grep -Po '"tag_name": "v\K[^"]*')
curl -Lo lazygit.tar.gz "https://github.com/jesseduffield/lazygit/releases/latest/download/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz"
tar xf lazygit.tar.gz lazygit
cd lazygit

sudo apt install fd-find
ln -snf $(which fdfind) ~/.local/bin/fd

sudo install lazygit /usr/local/bin

curl -s https://ohmyposh.dev/install.sh | bash -s -- -d ~/.local/bin



curl https://sh.rustup.rs -sSf | sh

sh <(curl -L https://nixos.org/nix/install) --no-daemon

nix --extra-experimental-features nix-command --extra-experimental-features flakes profile install github:kamadorueda/alejandra/3.0.0
```
