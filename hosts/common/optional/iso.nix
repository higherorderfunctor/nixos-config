{pkgs, ...}: {
  imports = [
    ../global/nix.nix
    ./openssh.nix
  ];

  # image generation
  isoImage.squashfsCompression = "gzip -Xcompression-level 1";

  # allow root on live CDs
  services.openssh.settings.PermitRootLogin = "yes";

  # make sure git is available (not part of minimal)
  environment.systemPackages = with pkgs; [git];
  programs.git.enable = true;
}
