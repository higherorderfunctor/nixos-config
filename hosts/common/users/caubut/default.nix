{
  config,
  inputs,
  pkgs,
  ...
}: let
  username = "caubut";
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  imports = [
    inputs.sops-nix.nixosModules.sops
  ];
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

  # TODO: # secrets
  # sops = {
  #   defaultSopsFile = ../secrets/secrets.yaml;
  #   secrets = {
  #     "${config.home.username}-secret-key" = {
  #       path = "${config.home.homeDirectory}/.ssh/id_ed25519";
  #       mode = "600";
  #     };
  #   };
  # };
  # persistence = {
  #   "/persist/home/caubut" = {
  #     directories = [
  #       "Documents"
  #       "Downloads"
  #       "Pictures"
  #       "Videos"
  #     ];
  #     files = [
  #       ".ssh/known_hosts"
  #     ];
  #     allowOther = true;
  #   };
  # };
  # environment.persistence."/persist".users.${username} = {
  #   directories = [
  #     "Documents"
  #     "Downloads"
  #     "Pictures"
  #     "Videos"
  #   ];
  #   files = [
  #     {
  #       file = ".ssh/id_ed25519";
  #       mode = "0600";
  #       parentDirectory = {mode = "0700";};
  #     }
  #   ];
  # };

  systemd.tmpfiles.rules = [
    "D /home/${username}/.ssh 0700 ${username} ${username} - -"
  ];
  sops.secrets = {
    # needs to be defined at the system config to use the system key to decrypt
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
