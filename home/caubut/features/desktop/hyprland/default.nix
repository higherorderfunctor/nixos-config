{
  inputs,
  pkgs,
  ...
}: {
  wayland.windowManager.hyprland = {
    enable = true;
    package = inputs.hyprland.packages.${pkgs.system}.hyprland;
    settings = {};
  };
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
