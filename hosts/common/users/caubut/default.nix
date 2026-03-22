{
  config,
  lib,
  pkgs,
  ...
}: let
  username = "caubut";
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  users.groups.${username} = {
    gid = 1000;
  };

  # FIXME:
  virtualisation.docker.enable = true;
  virtualisation.docker.storageDriver = "btrfs";
  virtualisation.docker.rootless = {
    enable = true;
    setSocketVariable = true;
  };

  users.users.${username} = {
    uid = 1000;
    group = "${username}";
    isNormalUser = true;
    shell = pkgs.zsh;
    extraGroups =
      [
        "wheel"
        "video"
        "audio"
      ]
      ++ ifGroupExist [
        "docker"
        "network"
        "media"
        "transmission" # TODO: had issues with just media
      ];
    hashedPasswordFile = config.sops.secrets."${username}-password".path;
    packages = [pkgs.home-manager];
  };

  # ulimit -a
  security.pam.loginLimits = [
    {
      # ulimit -Sn
      domain = "*";
      type = "soft";
      item = "nofile";
      value = 1048576;
    }
    {
      # ulimit -Hn # currently really high at 500k
      domain = "*";
      type = "hard";
      item = "nofile";
      value = 1048576;
    }
    {
      domain = "*";
      type = "-";
      item = "memlock";
      value = 1048576;
    }
  ];

  # TODO: ssh agent error in journal
  # TODO passwordless sudo not working

  # host specific home-manager configuration for user
  home-manager.users.caubut = import ../../../../home/${username}/hosts/${config.networking.hostName};
}
