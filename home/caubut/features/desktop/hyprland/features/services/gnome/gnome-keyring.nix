{
  config,
  lib,
  pkgs,
  ...
}: {
  services.gnome-keyring.enable = true;

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/keyrings")
    ];
  };
}
# ● gnome-keyring.service - GNOME Keyring
#      Loaded: loaded (/home/caubut/.config/systemd/user/gnome-keyring.service; enabled; preset: enabled)
#      Active: active (running) since Mon 2024-04-01 20:21:15 MDT; 1s ago
#    Main PID: 79587 (.gnome-keyring-)
#       Tasks: 5 (limit: 33280)
#      Memory: 1.1M (peak: 1.8M)
#         CPU: 7ms
#      CGroup: /user.slice/user-1000.slice/user@1000.service/app.slice/gnome-keyring.service
#              └─79587 /nix/store/1dmlapypmj6157bbp411p8456g4r7nrh-gnome-keyring-42.1/bin/gnome-keyring-daemon --start --foreground
#
# Apr 01 20:21:15 beelink-ser7 systemd[2765]: Started GNOME Keyring.
# Apr 01 20:21:15 beelink-ser7 gnome-keyring-daemon[79587]: gnome-keyring-daemon: no process capabilities, insecure memory might get used
# Apr 01 20:21:15 beelink-ser7 .gnome-keyring-[79587]: couldn't access control socket: /run/user/1000/keyring/control: No such file or directory
# Apr 01 20:21:15 beelink-ser7 gnome-keyring-daemon[79587]: couldn't access control socket: /run/user/1000/keyring/control: No such file or directory
# Apr 01 20:21:15 beelink-ser7 gnome-keyring-daemon[79587]: discover_other_daemon: 0
# Apr 01 20:21:15 beelink-ser7 gnome-keyring-daemon[79587]: discover_other_daemon: 0SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
