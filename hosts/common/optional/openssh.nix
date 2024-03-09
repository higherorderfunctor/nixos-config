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
# TODO:
#
# building the system configuration...
# trace: warning: caubut profile: You have enabled hyprland.systemd.enable or listed plugins in hyprland.plugins but do not have any configuration in hyprland.settings or hyprland.extraConfig. This is almost certainly a mistake.
# trace: warning: config.security.pam.sshAgentAuth.authorizedKeysFiles contains files in the user's home directory.
#
#         Specifying user-writeable files there result in an insecure configuration:
#         a malicious process can then edit such an authorized_keys file and bypass the ssh-agent-based authentication.
#         See https://github.com/NixOS/nixpkgs/issues/31611
