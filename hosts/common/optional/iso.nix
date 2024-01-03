_: {
  imports = [
    # enable extra options
    ../global/nix.nix
    # sshd
    ./openssh.nix
  ];

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # allow root on live CDs
  services.openssh.settings.PermitRootLogin = "yes";
}
