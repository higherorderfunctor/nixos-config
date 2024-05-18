{
  inputs,
  modulesPath,
  ...
}: {
  imports = [
    (modulesPath + "/installer/scan/not-detected.nix")
    inputs.nixos-hardware.nixosModules.common-pc-ssd
    inputs.nixos-hardware.nixosModules.common-cpu-amd-pstate
    inputs.nixos-hardware.nixosModules.common-cpu-amd-raphael-igpu
    inputs.nixos-hardware.nixosModules.common-gpu-amd
    ./disk-config.nix
    #../common/optional/wireless.nix
  ];

  nixpkgs.hostPlatform = "x86_64-linux";

  hardware = {
    amdgpu.amdvlk = true;
    opengl = {
      enable = true;
      # driSupport = true; # handled by common-gpu-amd
      # driSupport32Bit = true;
      # TODO all
    };
  };

  boot = {
    initrd = {
      availableKernelModules = [
        "nvme" # NVMe (Non-Volatile Memory Express) storage support
        "xhci_pci" # USB 3.0 (xHCI) PCI host controller support
        "thunderbolt" # Thunderbolt interface support
        "usbhid" # USB Human Interface Device (HID) support
        "usb_storage" # USB mass storage device support
        "sd_mod" # SCSI disk support
      ];
      kernelModules = [
        "dm-snapshot" # Device mapper snapshot support
        # FIXME: https://discourse.nixos.org/t/how-to-enable-ddc-brightness-control-i2c-permissions/20800/6
        "i2c-dev"
        # "ddcci_backlight"
      ];
    };
    kernelModules = [
      "kvm-amd" # KVM (Kernel-based Virtual Machine) support for AMD processors
    ];
    # extraModprobeConfig = ''
    #   options iwlwifi 11n_disable=1 swcrypto=0 bt_coex_active=0 power_save=0
    #   options iwlmvm power_scheme=1
    #   options iwlwifi d0i3_disable=1
    #   options iwlwifi uapsd_disable=1
    #   options iwlwifi lar_disable=1
    # '';
  };
}
#   boot.initrd.availableKernelModules = [ "nvme" "xhci_pci" "thunderbolt" "usbhid" ];
#   swapDevices = [ ];
# }
