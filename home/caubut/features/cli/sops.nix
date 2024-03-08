{
  config,
  inputs,
  pkgs,
  ...
}: {
  imports = [inputs.sops-nix.homeManagerModules.sops];

  home = {
    packages = [pkgs.sops];
    file = {
      ".ssh/personal_ed25519_key.pub".source = ../../secrets/personal_ed25519_key.pub;
      ".ssh/professional_ed25519_key.pub".source = ../../secrets/professional_ed25519_key.pub;
    };
  };

  sops = {
    defaultSopsFile = ../../secrets/secrets.yaml;
    age.sshKeyPaths = ["/home/${config.home.username}/.ssh/personal_ed25519_key"];
    secrets = {
      "${config.home.username}-personal-ed25519-key" = {
        path = "${config.home.homeDirectory}/.ssh/personal_ed25519_key";
        mode = "600";
      };
      "${config.home.username}-professional-ed25519-key" = {
        path = "${config.home.homeDirectory}/.ssh/professional_ed25519_key";
        mode = "600";
      };
    };
  };
}
