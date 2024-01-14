{
  config,
  lib,
  ...
}: let
  hasImpermanence = config.environment ? "persistence";
in {
  services.openssh = {
    enable = true;
    # require public key authentication for better security
    settings = {
      PasswordAuthentication = false;
      KbdInteractiveAuthentication = false;
      PermitRootLogin = lib.mkDefault "no";
    };
    hostKeys = [
      {
        path = "${lib.optionalString hasImpermanence "/persist"}/etc/ssh/ssh_host_ed25519_key";
        type = "ed25519";
      }
    ];
  };

  # passwordless sudo when SSHing with keys
  security.pam.sshAgentAuth.enable = true;
}
