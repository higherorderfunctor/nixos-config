{
  config,
  lib,
  ...
}: let
  cfg = config.services.servarr;
  mkUsers = start: names: let
    cfg =
      lib.foldl' (acc: name: {
        groups =
          acc.groups
          // {
            "${name}" = {
              gid = acc.next;
            };
          };
        users =
          acc.users
          // {
            "${name}" = {
              uid = acc.next;
              group = name;
              isSystemUser = true;
              extraGroups =
                if name != "servarr"
                then ["servarr"]
                else [];
            };
          };
        next = acc.next + 1;
      }) {
        groups = {};
        users = {};
        next = start;
      }
      names;
  in {inherit (cfg) groups users;};
in {
  imports = [
    ./vpn.nix
  ];

  options = {
    services.servarr.enable = lib.mkEnableOption "servarr";
  };

  config = lib.mkIf cfg.enable {
    users = mkUsers 4000 [
      "servarr"
      "unbound"
      "redis-unbound-cachedb"
    ];

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
