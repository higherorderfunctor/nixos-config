{...}: {
  imports = [
    ../common/optional/minimal-x86_64-linux-hardware-configuration.nix
  ];

  boot.initrd.availableKernelModules = ["ata_piix" "mptspi" "uhci_hcd" "nvme" "sr_mod"];
  boot.initrd.kernelModules = ["dm-snapshot"];
}
