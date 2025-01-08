{pkgs, ...}: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
    ../common/optional/openssh.nix
    ../common/optional/gnome # system support for Hyprland
    ../common/optional/networking/openconnect.nix
    # ../../modules/nixos/hyprgreet
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
  security.rtkit.enable = true; # FIXME: causes freeze on git push...?
  services.pipewire = {
    enable = true;
    alsa.enable = true;
    alsa.support32Bit = true;
    pulse.enable = true;
    jack.enable = true;
    wireplumber.enable = true;
    extraConfig.pipewire."92-low-latency" = {
      "context.properties" = {
        "default.clock.rate" = 44100;
        "default.clock.quantum" = 512;
        "default.clock.min-quantum" = 512;
        "default.clock.max-quantum" = 512;
      };
    };
    wireplumber.extraConfig = {
      # volume is by default set to 0.4.
      "60-defaults"."wireplumber.settings"."device.routes.default-sink-volume" = 1.0;
    };
    extraConfig.pipewire."60-microphone-rnnoise" = {
      "context.modules" = [
        {
          name = "libpipewire-module-filter-chain";
          args = {
            "node.description" = "Microphone (noise suppressed)";
            "media.name" = "Microphone (noise suppressed)";
            "filter.graph" = {
              nodes = [
                {
                  type = "ladspa";
                  name = "rnnoise";
                  plugin = "${pkgs.rnnoise-plugin}/lib/ladspa/librnnoise_ladspa.so";
                  label = "noise_suppressor_mono";
                  control = {
                    "VAD Threshold (%)" = 50.0;
                    "VAD Grace Period (ms)" = 200;
                    "Retroactive VAD Grace (ms)" = 0;
                  };
                }
              ];
            };
            "audio.rate" = 48000;
            "capture.props" = {
              "node.passive" = true;
              "node.name" = "rnnoise_input";
            };
            "playback.props" = {
              "media.class" = "Audio/Source";
              "node.name" = "rnnoise_output";
            };
          };
        }
      ];
    };
  };

  # NOTE: https://github.com/NixOS/nixpkgs/issues/319809
  # Do not use with pipewire
  # sound.enable = true;
  services.pulseaudio.enable = false;

  # TODO: https://nixos.wiki/wiki/JACK
  services.udev.extraRules = ''
    KERNEL=="rtc0", GROUP="audio"
    KERNEL=="hpet", GROUP="audio"
  '';
  security.pam.loginLimits = [
    {
      domain = "@audio";
      item = "memlock";
      type = "-";
      value = "unlimited";
    }
    {
      domain = "@audio";
      item = "rtprio";
      type = "-";
      value = "99";
    }
    {
      domain = "@audio";
      item = "nofile";
      type = "soft";
      value = "99999";
    }
    {
      domain = "@audio";
      item = "nofile";
      type = "hard";
      value = "99999";
    }
  ];

  # virtualisation.virtualbox = {
  #   host = {
  #     enable = true;
  #     enableExtensionPack = true;
  #   };
  #   guest = {
  #     enable = true;
  #     dragAndDrop = true;
  #   };
  # };

  users.extraGroups.vboxusers.members = ["caubut"];

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
