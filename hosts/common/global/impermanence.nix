{
  lib,
  inputs,
  config,
  ...
}: {
  imports = [
    inputs.impermanence.nixosModules.impermanence
  ];

  programs.fuse.userAllowOther = true;

  environment.persistence = {
    "/persist" = {
      hideMounts = true;
      directories = [
        "/srv"
        "/var/lib/nixos"
        "/var/lib/systemd"
        "/var/log"
      ];
      files = [
        "/etc/machine-id"
      ];
    };
  };

  system.activationScripts.persist-dirs.text = let
    mkHomePersist = user:
      lib.optionalString user.createHome ''
        mkdir -p /persist/${user.home}
        chown ${user.name}:${user.group} /persist/${user.home}
        chmod ${user.homeMode} /persist/${user.home}
      '';
    users = lib.attrValues config.users.users;
  in
    lib.concatLines (map mkHomePersist users);
}
