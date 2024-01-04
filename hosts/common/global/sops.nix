{inputs, ...}: {
  imports = [
    inputs.sops-nix.nixosModules.sops
  ];

  # https://github.com/Mic92/sops-nix/issues/427
  sops = {
    gnupg.sshKeyPaths = [];
    age.sshKeyPaths = ["/etc/nixos/home/caubut/id_ed25519"];
    defaultSopsFile = ../secrets.yaml;
  };
}
