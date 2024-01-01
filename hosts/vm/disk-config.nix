{config, ...}: {
  imports = [
    (import ../common/optional/root-luks-lvm.nix {keyFile = config.sops.secrets.vm-luks.path;})
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";
}
