{
  config,
  pkgs,
  ...
}: let
  username = "caubut";
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  # system configuration for user
  users.groups.${username} = {
    gid = 1000;
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
        "network"
      ];
    openssh.authorizedKeys.keys = [(builtins.readFile ../../../../home/${username}/secrets/id_ed25519.pub)];
    hashedPasswordFile = config.sops.secrets."${username}-password".path;
    packages = [pkgs.home-manager];
  };

  # TODO: ssh agent error in journal

  # permission fix from sops creating the ~/.ssh directory
  systemd.tmpfiles.rules = [
    "z /home/${username}/.ssh 0700 ${username} ${username} - -"
  ];

  # needs to be defined at the system config to use the system key to decrypt
  sops.secrets = {
    "${username}-secret-key" = {
      path = "${config.home-manager.users.${username}.home.homeDirectory}/.ssh/id_ed25519";
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
  home-manager.users.caubut = import ../../../../home/${username}/${config.networking.hostName}.nix;
}
