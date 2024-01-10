Download...

Download sig

gpg --keyserver-options auto-key-retrieve --verify archlinux-version-x86_64.iso.sig

Burn

Boot

# verify uefi
cat /sys/firmware/efi/fw_platform_size

iwctl
> device list
> station <device> connect <ssid>
> station <device> show
> exit
ping 9.9.9.9

timedatectl

fdisk -l

nvme id-ns -H /dev/nvme0n1 | grep "Relative Performance"

# look for best

# replace one with LBA format for best
nvme format --lbaf=1 /dev/nvme0n1

# recheck
nvme id-ns -H /dev/nvme0n1 | grep "Relative Performance"

# prep boot
fdisk /dev/nvme0n1
> g # new gpt table
> n # new part
> # <enter> default part number
> # <enter> default start sector
> +2048 # /efi size
> t # change part type
> 1 # efi
> n
> # <enter> # default part number
> # <enter> default start
> # <enter> default size
> p # check
> w # write

# format /efi
mkfs.fat -F 32 /dev/nvme0n1p1
# format /
cryptsetup -y -v luksFormat /dev/nvme0n1p2
> YES
> <pass phrase>
> <pass phrase>
cryptsetup open /dev/nvme0n1p2 cryptroot
mkfs.ext4 /dev/mapper/cryptroot

# mount
mount --mkdir /dev/mapper/cryptroot /mnt
mount --mkdir /dev/nvme0n1p1 /mnt/efi

# install base OS
pacstrap -K /mnt \
    base \
    linux-hardened \
    linux-firmware \
    dracut \
    sbsigntools \
    intel-ucode \ # intel
    amd-ucode     # amd
    lvm2 \
    openssh \
    git \
    iwd \
    efibootmgr
    neovim man-db man-pages texinfo
# fstab
genfstab -U /mnt >> /mnt/etc/fstab
cat /mnt/etc/fstab # review
arch-chroot /mnt
ln -sf /usr/share/zoneinfo/America/Denver /etc/localtime
hwclock --systohc
nvim /etc/locale.gen
# uncomment
en_US.UTF-8 UTF-8
:wq
locale-gen
nvim /etc/locale.conf
LANG=en_US.UTF-8
:wq
echo ser7 > /etc/hostname
passwd
> <password>
> <password>

bootctl install
# CHECK THOSE WARNING!!!!!
https://wiki.archlinux.org/title/Systemd-boot#Installing_the_EFI_boot_manager
https://wiki.archlinux.org/title/User:Krin/Secure_Boot,_full_disk_encryption,_and_TPM2_unlocking_install
section 1.3 updating boot manager
!! AND SECURE BOOT



nvim /etc/loader/loader.conf
default  arch.conf
timeout  3
console-mode max
editor   no
:wq
