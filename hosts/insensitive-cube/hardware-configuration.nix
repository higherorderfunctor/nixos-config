{
  inputs,
  lib,
  modulesPath,
  ...
}: {
  imports = [
    (modulesPath + "/installer/scan/not-detected.nix")
    inputs.nixos-hardware.nixosModules.common-pc-ssd
    inputs.nixos-hardware.nixosModules.common-cpu-intel
    inputs.nixos-hardware.nixosModules.common-gpu-intel
    # ../common/optional/wireless.nix
  ];

  root-luks-lvm-btrfs2 = {
    enable = true;
    device = "/dev/nvme0n1";
    swapSize = "16G";
  };

  hardware = {
    intelgpu.enableHybridCodec = true;
    enableAllFirmware = true; # enable all firmware regardless of licence
  };

  boot = {
    initrd = {
      availableKernelModules = [
        "ahci" # Advanced Host Controller Interface for SATA support
        "nvme" # NVMe (Non-Volatile Memory Express) storage support
        "sd_mod" # SCSI disk support
        "thunderbolt" # Thunderbolt interface support
        "usb_storage" # USB mass storage device support
        "usbhid" # USB Human Interface Device (HID) support
        "xhci_pci" # USB 3.0 (xHCI) PCI host controller support
      ];
      kernelModules = [
        "dm-snapshot" # Device mapper snapshot support
        # FIXME: https://discourse.nixos.org/t/how-to-enable-ddc-brightness-control-i2c-permissions/20800/6
        # "i2c-dev"
        # "ddcci_backlight"
      ];
    };
    kernel.sysctl = {
      # Maximum percentage of system memory that can be filled with "dirty"
      # (modified but not yet written to disk) pages.
      "vm.dirty_ratio" = 60;
      # Background writeback threshold: when dirty pages exceed this percentage,
      # the kernel starts writing them to disk in the background.
      "vm.dirty_background_ratio" = 5;
      # Controls how aggressively the kernel swaps memory pages. Lower = less
      # swapping. 10 is conservative (good for SSDs and responsiveness).
      "vm.swappiness" = 10;
      # Controls how aggressively the kernel reclaims memory used for caching
      # directory and inode objects. Lower = keep cache longer (better
      # performance), higher = free cache faster (more memory available).
      "vm.vfs_cache_pressure" = 50;
    };
    kernelModules = [
      "kvm-intel" # KVM (Kernel-based Virtual Machine) support for Intel processors
    ];
    extraModulePackages = [];
  };

  # Enables DHCP on each ethernet and wireless interface. In case of scripted networking
  # (the default) this is the recommended approach. When using systemd-networkd it's
  # still possible to use this option, but it's recommended to use it in conjunction
  # with explicit per-interface declarations with `networking.interfaces.<interface>.useDHCP`.
  networking = {
    useDHCP = lib.mkDefault true;
    interfaces.enp8s0.useDHCP = lib.mkDefault true;
    interfaces.wlp7s0.useDHCP = lib.mkDefault true;
  };

  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";
}
