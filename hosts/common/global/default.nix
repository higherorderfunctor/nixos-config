{specialArgs, ...}: {
  imports = [
    specialArgs.inputs.disko.nixosModules.disko
  ];

  system.stateVersion = "24.05";
}
