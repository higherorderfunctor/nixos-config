{
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  # allowed SSH users
  users.users.root.openssh.authorizedKeys.keys = [
    (builtins.readFile ../../../home/caubut/secrets/personal_ed25519_key.pub)
  ];

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # allow root on live CDs
  services.openssh.settings.PermitRootLogin = "yes";

  # make sure git is available (not part of minimal)
  programs.git.enable = true;
}
