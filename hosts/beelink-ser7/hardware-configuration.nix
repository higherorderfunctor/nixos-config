{
  config,
  inputs,
  lib,
  modulesPath,
  ...
}: {
  imports = [
    ../common/optional/minimal-x86_64-linux-hardware-configuration.nix
    (modulesPath + "/installer/scan/not-detected.nix")
    inputs.hardware.nixosModules.common-pc-ssd
    inputs.hardware.nixosModules.common-cpu-amd
    inputs.hardware.nixosModules.common-gpu-amd
  ];

  boot = {
    initrd = {
      availableKernelModules = [
        "nvme"
        "xhci_pci"
        "thunderbolt"
        "usbhid"
        "usb_storage"
        "sd_mod"
      ];
      kernelModules = ["dm-snapshot"];
    };
    kernelModules = ["kvm-amd"];
  };
  hardware.cpu.amd.updateMicrocode = lib.mkDefault config.hardware.enableRedistributableFirmware;
}
