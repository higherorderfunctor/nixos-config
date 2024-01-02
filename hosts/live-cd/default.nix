{inputs, ...}: {
  imports = [
    # base image
    "${inputs.nixos}/nixos/modules/installer/cd-dvd/installation-cd-minimal.nix"
    # enable extra options
    ../common/global/nix.nix
  ];

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # enable SSH
  systemd.services.sshd.wantedBy = inputs.nixos.lib.mkForce ["multi-user.target"];

  # networking
  networking.networkmanager.enable = true;

  # add authorized public key(s)
  users.users.root.openssh.authorizedKeys.keys = [
    (builtins.readFile ../../home/caubut/ssh.pub)
  ];
}
