{inputs, ...}: {
  imports = [
    inputs.sops-nix.nixosModules.sops
  ];

  sops.age.sshKeyPaths = ["/etc/nixos/home/caubut/id_ed25519.pub"];
  sops.defaultSopsFile = ../secrets.yaml;
}
