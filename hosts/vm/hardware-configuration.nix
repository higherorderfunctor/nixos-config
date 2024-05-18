{
  inputs,
  lib,
  ...
}: {
  imports = [
    inputs.nixos-hardware.nixosModules.common-pc-ssd
    ./disk-config.nix
  ];

  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";

  hardware.opengl = {
    enable = true;
    driSupport = true;
    driSupport32Bit = true;
    # TODO all
  };

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
