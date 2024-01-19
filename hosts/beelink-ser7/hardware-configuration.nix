{
  inputs,
  modulesPath,
  ...
}: {
  imports = [
    (modulesPath + "/installer/scan/not-detected.nix")
    inputs.hardware.nixosModules.common-pc-ssd
    inputs.hardware.nixosModules.common-cpu-amd
    inputs.hardware.nixosModules.common-gpu-amd
    ./disk-config.nix
    ../common/optional/wireless.nix
  ];

  nixpkgs.hostPlatform = "x86_64-linux";

  hardware.opengl = {
    enable = true;
    driSupport = true;
    driSupport32Bit = true;
    # TODO all
  };

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
    extraModprobeConfig = ''
      options iwlwifi 11n_disable=1 swcrypto=0 bt_coex_active=0 power_save=0
      options iwlmvm power_scheme=1
      options iwlwifi d0i3_disable=1
      options iwlwifi uapsd_disable=1
      options iwlwifi lar_disable=1
    '';
  };
}
