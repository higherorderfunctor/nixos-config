{
  config,
  pkgs,
  ...
}: let
  username = "caubut";
  userConfig = ../../../../home/${username};
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
    openssh.authorizedKeys.keys = [(builtins.readFile "${userConfig}/secrets/id_ed25519.pub")];
    hashedPasswordFile = config.sops.secrets."${username}-password".path;
    packages = [pkgs.home-manager];
  };

  # # secrets
  # sops = {
  #   defaultSopsFile = ../secrets/secrets.yaml;
  #   secrets = {
  #     "${config.home.username}-secret-key" = {
  #       path = "${config.home.homeDirectory}/.ssh/id_ed25519";
  #       mode = "600";
  #     };
  #   };
  # };
  environment.persistence."/persist" = {
    users.${username} = {
      files = [
        {
          file = ".ssh/id_ed25519";
          mode = "0600";
          parentDirectory = {mode = "0700";};
        }
      ];
    };
  };

  sops.secrets = {
    "${config.home.username}-secret-key" = {
      path = "${config.home.homeDirectory}/.ssh/id_ed25519";
      mode = "600";
    };
    "${username}-password" = {
      neededForUsers = true;
      sopsFile = "${userConfig}/secrets/secrets.yaml";
    };
  };

  # host specific home-manager configuration for user
  home-manager.users.caubut = import ../../../../home/${username}/${config.networking.hostName}.nix;
}
