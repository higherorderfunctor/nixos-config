{
  config,
  inputs,
  pkgs,
  ...
}: {
  imports = [inputs.sops-nix.homeManagerModules.sops];

  home.packages = [pkgs.sops];

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
