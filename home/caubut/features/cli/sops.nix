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
      activation.reload-secrets = config.lib.dag.entryAfter ["writeBoundary"] ''
        /usr/bin/systemctl start --user sops-nix
      '';
    };

  sops = {
    gnupg.sshKeyPaths = [];
    age.sshKeyPaths = [
      "/home/${config.home.username}/.ssh/personal_ed25519_key"
      # starter key for non-nixos systems (can be removed after first activation)
      "/home/${config.home.username}/.ssh/id_ed25519"
    ];
    defaultSopsFile = ../../secrets/secrets.yaml;
  };
}
