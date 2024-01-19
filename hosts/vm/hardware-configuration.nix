{
  inputs,
  lib,
  ...
}: {
  imports = [
    inputs.hardware.nixosModules.common-pc-ssd
    ./disk-config.nix
  ];

  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";

  hardware.opengl.enable = true;

  boot = {
    initrd = {
      availableKernelModules = [
        "ata_piix"
        "ohci_pci"
        "ehci_pci"
        "nvme"
        "sr_mod"
      ];
      kernelModules = ["dm-snapshot"];
    };
  };
}
