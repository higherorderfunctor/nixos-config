{
  config,
  pkgs,
  ...
}: let
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  # system configuration for user
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
    openssh.authorizedKeys.keys = [(builtins.readFile ../../../../home/caubut/id_ed25519.pub)];
    hashedPasswordFile = config.sops.secrets.caubut-password.path;
    packages = [pkgs.home-manager];
  };

  sops.secrets.caubut-password = {
    neededForUsers = true;
  };

  # host specific home-manager configuration for user
  home-manager.users.caubut = import ../../../../home/caubut/${config.networking.hostName}.nix;
}
