{lib, ...}: {
  imports = [
    ../../global
    ../../features/desktop
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
  # fix for non-nixos systems
  targets.genericLinux.enable = true;
}
