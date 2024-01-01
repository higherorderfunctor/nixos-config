{
  config,
  pkgs,
  ...
}: {
  users.mutableUsers = false;
  users.users.caubut = {
    isNormalUser = true;
    shell = pkgs.zsh;
    extraGroups = [
      "wheel"
      "video"
      "audio"
    ];
    hashedPasswordFile = config.sops.secrets.caubut-password.path;
    packages = [pkgs.home-manager];
  };

  sops.secrets.caubut-password = {
    sopsFile = ../../secrets.yaml;
    neededForUsers = true;
  };

  # TODO descrypt secrets on login?  user service
  # TODO: home-manager.users.caubut = import ../../../../home/misterio/${config.networking.hostName}.nix;
}
