#!/bin/bash

set -euETo pipefail
shopt -s inherit_errexit

# configuration
BTRFS_MOUNT="${BTRFS_MOUNT:-/btrfs}"
VOLUME_DEVICE="${VOLUME_DEVICE:-/dev/mapper/cryptlvm-root}"
MAX_AGE_DAYS="${MAX_AGE_DAYS:-30}"
KEEP_SNAPSHOTS="${KEEP_SNAPSHOTS:-5}"

if [[ -n "${SUBVOLUMES:-}" ]]; then
	IFS=' ' read -ra SUBVOLUMES <<<"$SUBVOLUMES"
else
	SUBVOLUMES=("root" "home")
fi

# library functions
delete_subvolume_recursively() {
	while read -r i; do
		delete_subvolume_recursively "$BTRFS_MOUNT/$i"
	done < <(btrfs subvolume list -o "$1" | cut -f 9- -d ' ')
	btrfs subvolume delete "$1"
}

backup_subvolume() {
	local subvol="$1"
	local snapshot_dir="$BTRFS_MOUNT/snapshots/$subvol"

	if [[ -e "$BTRFS_MOUNT/$subvol" ]]; then
		mkdir -p "$snapshot_dir"
		timestamp=$(date --date="@$(stat -c %Y "$BTRFS_MOUNT/$subvol")" "+%Y-%m-%d_%H:%M:%S")
		mv "$BTRFS_MOUNT/$subvol" "$snapshot_dir/$timestamp"
	fi
}

clean_old_snapshots() {
	local snapshot_dir="$1"

	# skip if directory doesn't exist
	[[ -d "$snapshot_dir" ]] || return 0

	# get the old snapshots, then process them if any exist
	mapfile -t old_snapshots < <(
		find "$snapshot_dir" -maxdepth 1 -mtime +"$MAX_AGE_DAYS" |
			sort |
			cut -d' ' -f2 |
			head -n -"$KEEP_SNAPSHOTS"
	)

	for i in "${old_snapshots[@]}"; do
		[[ -n "$i" ]] && delete_subvolume_recursively "$i"
	done
}

# main script
mkdir -p "$BTRFS_MOUNT"
mount -t btrfs "$VOLUME_DEVICE" "$BTRFS_MOUNT"

for subvol in "${SUBVOLUMES[@]}"; do
	backup_subvolume "$subvol"
	clean_old_snapshots "$BTRFS_MOUNT/snapshots/$subvol"
	# rollback to blank volume
	btrfs subvolume create "$BTRFS_MOUNT/$subvol"
done

umount "$BTRFS_MOUNT"
rmdir "$BTRFS_MOUNT"
