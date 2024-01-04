{
  config,
  pkgs,
  ...
}: let
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  users.mutableUsers = false;
  users.users.caubut = {
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
    hashedPasswordFile = config.sops.secrets.caubut-password.path;
    packages = [pkgs.home-manager];
  };

  sops.secrets.caubut-password = {
    neededForUsers = true;
  };

  # TODO descrypt secrets on login?  user service
  # TODO: home-manager.users.caubut = import ../../../../home/misterio/${config.networking.hostName}.nix;
}
