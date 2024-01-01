{...}: {
  imports = [
    ../common/optional/root-luks-lvm.nix
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";
  # TODO SSD type stuff https://nixos.wiki/wiki/Nixos-generate-config:wiki
}
