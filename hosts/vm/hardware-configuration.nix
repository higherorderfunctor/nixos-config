{inputs, ...}: {
  imports = [
    ../common/optional/minimal-x86_64-linux-hardware-configuration.nix
    inputs.hardware.nixosModules.common-pc-ssd
    ./disk-config.nix
  ];

  boot = {
    initrd = {
      availableKernelModules = ["ata_piix" "mptspi" "uhci_hcd" "nvme" "sr_mod"];
      kernelModules = ["dm-snapshot"];
    };
  };
}
