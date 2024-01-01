# minimal configuration to use for disko
{
  inputs,
  lib,
  ...
}: {
  imports = [
    inputs.disko.nixosModules.disko
  ];
  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";
}
