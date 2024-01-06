{
  config,
  inputs,
  ...
}: let
  isEd25519 = k: k.type == "ed25519";
  getKeyPath = k: k.path;
  keys = builtins.filter isEd25519 config.services.openssh.hostKeys;
in {
  imports = [
    inputs.sops-nix.nixosModules.sops
  ];

  # https://github.com/Mic92/sops-nix/issues/427
  sops = {
    gnupg.sshKeyPaths = [];
    age.sshKeyPaths = map getKeyPath keys;
    defaultSopsFile = ../../${config.networking.hostName}/secrets/secrets.yaml;
  };
}
