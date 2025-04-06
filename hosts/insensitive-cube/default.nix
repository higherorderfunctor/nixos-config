{
  imports = [
    ../common/optional/root-luks-lvm-btrfs.nix
  ];

  # configure the root device
  config.root-luks-lvm-btrfs2 = {
    device = "/dev/nvme0n1";
    swapSize = "16G";
  };
}
#   # Bootloader.
#   boot.loader.systemd-boot.enable = true;
#   boot.loader.efi.efiSysMountPoint = "/boot";
#   boot.loader.efi.canTouchEfiVariables = true;
#   boot.initrd.systemd.enable = true;
#
#   boot.initrd.luks.devices = {
#     cryptroot = {
#        device = "/dev/disk/by-partuuid/${partitionuuid}";
#        allowDiscards = true; # Used if primary device is a SSD
#        preLVM = true;
#     };
#   };
#
#   environment.systemPackages = with pkgs; [
#     sbctl
#     tpm2-tools
#     tpm2-tss
#   ];
#
# Nix
#
# boot.lanzaboote = {
#   enable = true;
#   pkiBundle = "/etc/secureboot";
# };
#
#     Generate and enroll your own keys (since NixOS doesn't use Microsoft's keys):
#
# Bash
#
# # Install sbctl
# nix-env -iA nixos.sbctl
#
# # Create keys
# sudo sbctl create-keys
#
# # Enroll keys in firmware
# sudo sbctl enroll-keys
#
#     Update your TPM configuration to include PCR 7 (Secure Boot state):
#
# Bash
#
# sudo systemd-cryptenroll --tpm2-device=auto --tpm2-pcrs=7+0+1+2+3+4 /dev/sdXY
