{
  inputs,
  pkgs,
  ...
}: {
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  environment.etc = {
    "ssh/authorized_keys.d/root" = {
      text = pkgs.lib.mkDefault (
        pkgs.lib.mkAfter (
          builtins.readFile inputs.nixos-secrets.secretFiles.personalPubKey
        )
      );
      mode = "0444";
    };
  };

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # allow root on live CDs
  services.openssh.settings.PermitRootLogin = "yes";

  # make sure git is available (not part of minimal)
  programs.git.enable = true;
}
