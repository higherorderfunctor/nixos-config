{lib, ...}: {
  services.openssh = {
    enable = true;
    # require public key authentication for better security
    settings = {
      PasswordAuthentication = false;
      KbdInteractiveAuthentication = false;
      PermitRootLogin = lib.mkDefault "no";
    };
  };

  # add authorized public key(s)
  users.users.root.openssh.authorizedKeys.keys = [
    (builtins.readFile ../../../home/caubut/id_ed25519.pub)
  ];

  # passwordless sudo when SSH'ing with keys
  security.pam.enableSSHAgentAuth = true;
}
