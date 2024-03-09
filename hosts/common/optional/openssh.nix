{lib, ...}: {
  services.openssh = {
    enable = true;
    # require public key authentication for better security
    settings = {
      PasswordAuthentication = false;
      KbdInteractiveAuthentication = false;
      PermitRootLogin = lib.mkDefault "no";
    };
    # https://github.com/NixOS/nixpkgs/issues/31611
    authorizedKeysFiles =
      lib.mkForce ["/etc/ssh/authorized_keys.d/%u"];
  };
  # passwordless sudo when with keys
  security.pam.sshAgentAuth.enable = true;
}
