{
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  # allowed SSH users
  services.openssh.authorizedKeysFiles = [
    "ssh/authorized_keys.d/root/personal_ed25519_key.pub"
  ];

  environment.etc = {
    "ssh/authorized_keys.d/root/personal_ed25519_key.pub" = {
      source = ../../../caubut/secrets/personal_ed25519_key.pub;
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
