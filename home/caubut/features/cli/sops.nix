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
    age.sshKeyPaths = ["/home/${config.home.username}/.ssh/personal_ed25519_key"];
    defaultSopsFile = ../../secrets/secrets.yaml;
  };
}
