{inputs, ...}: final: prev: let
  inherit (inputs.nixpkgs) lib;
in
  prev
  // rec {
    # https://gist.github.com/udf/4d9301bdc02ab38439fd64fbda06ea43
    # https://github.com/Conquerix/wirenix/blob/6315ea07e44b38a293f36f5380f715907af2abe6/wire.nix#L132
    # https://github.com/dlo9/nixos-config/blob/7223e7d11074ed6aaa08ba26490f7e1b05fdb15d/system/nixos/admin.nix#L17
    mkMergeTopLevel = names: attrs:
      final.getAttrs names (
        final.mapAttrs
        (_: v: final.mkMerge v)
        (final.foldAttrs (n: a: [n] ++ a) [] attrs)
      );

    mkSafeMerge = possibleTopLevelKeys: attrs: (
      mkMergeTopLevel
      possibleTopLevelKeys
      ((final.singleton (final.genAttrs possibleTopLevelKeys (_: {}))) ++ attrs)
    );

    mkUsers = start: names: let
      cfg =
        final.foldl' (acc: name: {
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

    shared = {
      config = {
        nix = {
          settings = {
            cores = lib.mkForce 4;
            max-jobs = lib.mkForce 1;
            trusted-users = ["root" "@wheel"];
            auto-optimise-store = lib.mkDefault true;
            experimental-features = ["nix-command" "flakes"];
            substituters = [
              "https://cache.nixos.org/"
              "https://nix-community.cachix.org"
              "https://hyprland.cachix.org"
              "https://wezterm.cachix.org"
            ];
            trusted-public-keys = [
              "cache.nixos.org-1:6NCHdD59X431o0gWypbMrAURkbJ16ZPMQFGspcDShjY="
              "hyprland.cachix.org-1:a7pgxzMz7+chwVL3/pzj6jIBMioiJM7ypFP8PwtkuGc="
              "nix-community.cachix.org-1:mB9FSh9qf2dCimDSUo8Zy7bkq5CX+/rkCWyvRCYg3Fs="
              "wezterm.cachix.org-1:kAbhjYUC9qvblTE+s7S+kl5XM1zVa4skO+E/1IDWdH0="
            ];
          };
          gc = {
            automatic = true;
            # dates = "weekly";
            # Keep the last 60 days of generations
            options = "--delete-older-than 60d";
          };
        };
      };
    };
  }
