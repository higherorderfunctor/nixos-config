{
  config,
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
        "servarr"
        "transmission" # TODO: had issues with just media
      ];
    hashedPasswordFile = config.sops.secrets."${username}-password".path;
    packages = [pkgs.home-manager];
  };

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
  ];

  environment.etc = {
    "ssh/authorized_keys.d/${username}" = {
      text = pkgs.lib.mkDefault (
        pkgs.lib.mkAfter (
          builtins.readFile ../../../../home/${username}/secrets/personal_ed25519_key.pub
        )
      );
      mode = "0444";
    };
  };

  # TODO: ssh agent error in journal
  # TODO passwordless sudo not working

  # defines at system level since there is no
  # key for home manager to unlock secrets
  sops.secrets = {
    "${username}-personal-ed25519-key" = {
      owner = "${username}";
      mode = "400";
      sopsFile = ../../../../home/${username}/secrets/secrets.yaml;
    };
    "${username}-password" = {
      neededForUsers = true;
      sopsFile = ../../../../home/${username}/secrets/secrets.yaml;
    };
  };

  # host specific home-manager configuration for user
  home-manager.users.caubut = import ../../../../home/${username}/hosts/${config.networking.hostName};
}
