{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  imports = [inputs.sops-nix.homeManagerModules.sops];

  home =
    {
      packages = [pkgs.sops];
    }
    # conditionally enabled on non-nixos systems
    // lib.optionalAttrs config.targets.genericLinux.enable
    {
      activation = {
        reload-secrets = config.lib.dag.entryAfter ["writeBoundary"] ''
          /usr/bin/systemctl start --user sops-nix
        '';
      };
    };

  sops = {
    gnupg.sshKeyPaths = [];
    age.sshKeyPaths = [
      "/home/${config.home.username}/.ssh/personal_ed25519_key"
      # starter key for non-nixos systems (can be removed after first activation)
      "/home/${config.home.username}/.ssh/id_ed25519"
    ];
    defaultSopsFile = ../../secrets/secrets.yaml;
    # TODO: https://github.com/Mic92/sops-nix/pull/305
    # https://discourse.nixos.org/t/access-nixos-sops-secret-via-home-manager/38909/10
    defaultSymlinkPath = "/run/user/1000/secrets";
    defaultSecretsMountPoint = "/run/user/1000/secrets.d";
    secrets = {
      "${config.home.username}-age-keys" = {
        path = "${config.xdg.configHome}/sops/age/keys.txt";
        mode = "400";
      };
    };
  };
}
