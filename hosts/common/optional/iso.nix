{}: let
  username = "caubut";
in {
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  environment.etc = {
    # https://github.com/NixOS/nixpkgs/issues/31611
    "ssh/authorized_keys.d/root/personal_ed25519_key.pub" = {
      source = ../../../home/caubut/secrets/personal_ed25519_key.pub;
      mode = "0444";
    };
  };

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # allow root on live CDs
  services.openssh.settings.PermitRootLogin = "yes";

  # make sure git is available (not part of minimal)
  programs.git.enable = true;
}
