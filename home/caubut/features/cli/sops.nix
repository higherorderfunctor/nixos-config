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
}
