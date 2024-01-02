{inputs, ...}: {
  imports = [
    # base image
    "${inputs.nixos}/nixos/modules/installer/cd-dvd/installation-cd-minimal.nix"
    ../common/optional/iso.nix
  ];
}
