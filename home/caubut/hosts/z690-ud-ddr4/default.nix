{lib, ...}: {
  imports = [
    ../../global
    ../../features/cli/nix.nix
    ../../features/desktop
    ../../features/system/nix-gl-host.nix
    ../../features/system/openconnect.nix
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
  # fix for non-nixos systems
  targets.genericLinux.enable = true;
}
