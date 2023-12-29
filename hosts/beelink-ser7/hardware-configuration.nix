{
  imports = [
  ];

  boot = {
    initrd = {
      availableKernelModules = ["nvme" "xhci_pci" "ahci" "usb_storage" "usbhid" "sd_mod"];
      kernelModules = ["kvm-amd"];
    };
    loader = {
      systemd-boot = {
        enable = true;
        consoleMode = "max";
      };
      efi.canTouchEfiVariables = true;
    };
  };

  fileSystems = {
    "/boot" = {
      device = "/dev/disk/by-label/ESP";
      fsType = "vfat";
    };
    "/" = {
      device = "/dev/disk/by-label/dm-name-pool-root";
      fsType = "ext4";
    };
  };

  nixpkgs.hostPlatform.system = "x86_64-linux";
  # hardware.cpu.amd.updateMicrocode = true;
}
