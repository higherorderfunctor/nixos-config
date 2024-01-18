{
  inputs,
  lib,
  ...
}: {
  imports = [
    "${inputs.nixos}/nixos/modules/installer/cd-dvd/installation-cd-minimal.nix"
    ../common/optional/iso.nix
  ];
  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";
}
