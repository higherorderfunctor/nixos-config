{inputs, ...}: {
  # enable SSH
  systemd.services.sshd.wantedBy = inputs.nixos.lib.mkForce ["multi-user.target"];

  # add authorized public key(s)
  users.users.root.openssh.authorizedKeys.keys = [
    (builtins.readFile ../../../home/caubut/ssh.pub)
  ];
}
