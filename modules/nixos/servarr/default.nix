{
  config,
  lib,
  ...
}: let
  cfg = config.services.servarr;
in {
  imports = [
    ./vpn.nix
  ];

  options = {
    services.servarr.enable = lib.mkEnableOption "servarr";
  };

  config = lib.mkIf cfg.enable {
    users = {
      groups = {
        # adds a common group for this service between the host and containers
        servarr = {
          gid = 4000;
        };
      };
      users = {
        # adds a common user for this service to own files between the host and containers
        servarr = {
          uid = 4000;
          group = "servarr";
          isSystemUser = true;
        };
      };
    };

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
