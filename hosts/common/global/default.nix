{inputs, ...}: {
  imports = [
    inputs.disko.nixosModules.disko
  ];

  # system state version
  system.stateVersion = "24.05";

  # bootloader
  boot.loader = {
    systemd-boot = {
      enable = true;
      consoleMode = "max";
    };
    efi.canTouchEfiVariables = true;
  };

  # disko scripts
  # TODO what these for
  # environment.systemPackages = with pkgs; [
  #   (pkgs.writeScriptBin "disko-create" (disko.create cfg))
  #   (pkgs.writeScriptBin "disko-mount" (disko.mount cfg))
  # ];
}