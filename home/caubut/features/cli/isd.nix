{
  inputs,
  pkgs,
  ...
}: {
  home.packages = [inputs.isd.packages.${pkgs.system}.default];
}
