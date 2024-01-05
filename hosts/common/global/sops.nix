{
  config,
  inputs,
  ...
}: {
  imports = [
    inputs.sops-nix.nixosModules.sops
  ];

  # https://github.com/Mic92/sops-nix/issues/427
  sops = {
    gnupg.sshKeyPaths = [];
    age.sshKeyPaths = ["/etc/ssh/ssh_host_ed25519_key"];
    defaultSopsFile = ../../${config.networking.hostName}/secrets/secrets.yaml;
  };
}
