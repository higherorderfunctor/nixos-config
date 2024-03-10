{...}: {
  imports = [
    ./hardware-configuration.nix
    ../common/global
    ../common/optional/openssh.nix
  ];

  # hostname
  networking.hostName = "beelink-ser7";

  # TODO:
  # https://nixos.wiki/wiki/PipeWire
  # rtkit is optional but recommended
  security.rtkit.enable = true;
  services.pipewire = {
    enable = true;
    alsa.enable = true;
    alsa.support32Bit = true;
    pulse.enable = true;
    # If you want to use JACK applications, uncomment this
    #jack.enable = true;
  };
}
