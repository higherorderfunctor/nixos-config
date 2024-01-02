{inputs, ...}: {
  imports = [
    # base image
    "${inputs.nixos}/nixos/modules/installer/cd-dvd/installation-cd-graphical-gnome.nix"
    ../common/optional/iso.nix
  ];
}
