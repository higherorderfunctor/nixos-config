{inputs, ...}: {
  imports = ["${inputs.nixos}/nixos/modules/installer/cd-dvd/installation-cd-minimal.nix"];
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";
  systemd.services.sshd.wantedBy = inputs.nixos.lib.mkForce ["multi-user.target"];
  users.users.root.openssh.authorizedKeys.keys = [(builtins.readFile ../../home/caubut/ssh.pub)];
}
