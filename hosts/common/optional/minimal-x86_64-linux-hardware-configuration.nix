# minimal configuration to use for disko
{lib, ...}: {
  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";
}
