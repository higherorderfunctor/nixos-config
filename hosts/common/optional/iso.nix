_: {
  imports = [
    # enable extra options
    ../global/nix.nix
    # sshd
    ./sshd.nix
  ];

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";
}
