{pkgs, ...}: {
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  environment.etc = {
    "ssh/authorized_keys.d/root" = {
      text = pkgs.lib.mkDefault (
        pkgs.lib.mkAfter (
          builtins.readFile ../../../home/caubut/secrets/personal_ed25519_key.pub
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
