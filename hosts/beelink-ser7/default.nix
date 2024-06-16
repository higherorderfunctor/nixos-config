{pkgs, ...}: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
    ../common/optional/openssh.nix
    ../common/optional/gnome # system support for Hyprland
    ../common/optional/networking/openconnect.nix
    ../../modules/nixos/hyprgreet
    ./services/servarr.nix
    ./virtualisation
  ];

  # hostname
  networking.hostName = "beelink-ser7";

  # TODO: linking with btop
  environment.systemPackages = with pkgs; [
    rocmPackages.rocm-smi
    radeontop
    mesa-demos
    vulkan-tools
  ];

  # TODO:
  #https://nixos.wiki/wiki/PipeWire
  # rtkit is optional but recommended
  security.rtkit.enable = true;
  services.pipewire = {
    enable = true;
    alsa.enable = true;
    alsa.support32Bit = true;
    pulse.enable = true;
    # If you want to use JACK applications, uncomment this
    # jack.enable = true;
  };

  # TODO: test

  programs.firefox.policies = {
    DisableTelemetry = true;
    DisableFirefoxStudies = true;
    EnableTrackingProtection = {
      Value = true;
      Locked = true;
      Cryptomining = true;
      Fingerprinting = true;
    };
    DisablePocket = true;
    OverrideFirstRunPage = "";
    OverridePostUpdatePage = "";
    DontCheckDefaultBrowser = true;
    DisplayMenuBar = "default-off";
    SearchBar = "separate";
    ExtensionSettings = {
      # uBlock Origin:
      "uBlock0@raymondhill.net" = {
        install_url = "https://addons.mozilla.org/firefox/downloads/latest/ublock-origin/latest.xpi";
        installation_mode = "force_installed";
      };
    };
  };
}
