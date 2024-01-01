{config, ...}: {
  imports = [
    ../common/optional/root-luks-lvm.nix
  ];

  # set the root device
  disko.devices.disk.root.device = "/dev/nvme0n1";

  disko.devices.disk.root.content.luls.content.settings = {
    keyFile = config.sops.secrets.vm-luks.path;
    allowDiscards = true;
  };
}
