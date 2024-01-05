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

  # passwordless sudo when SSH'ing with keys
  security.pam.enableSSHAgentAuth = true;
}
