{
  config,
  lib,
  ...
}: let
  cfg = config.services.servarr;
  users = import ./users.nix { inherit lib; };
in {
  imports = [
    ./vpn.nix
  ];

  options = {
    services.servarr.enable = lib.mkEnableOption "servarr";
  };

  config = lib.mkIf cfg.enable {
    inherit users;

    environment.persistence."/persist" = {
      hideMounts = true;
      directories = [
        # persistent files between containers
        {
          directory = "/var/lib/servarr";
          user = "servarr";
          group = "servarr";
          mode = "u=rwx,g=rwx,o=g+s";
        }
      ];
    };

    # fixes permissions and the sgid not applying
    systemd.tmpfiles.rules = [
      "z /persist/var/lib/servarr 2770 servarr servarr - -"
      "z /var/lib/servarr 2770 servarr servarr - -"
    ];
  };
}
