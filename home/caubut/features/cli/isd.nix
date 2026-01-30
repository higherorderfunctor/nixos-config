{
  inputs,
  pkgs,
  ...
}: {
  home.packages = [inputs.isd.packages.${pkgs.stdenv.hostPlatform.system}.default];
}
