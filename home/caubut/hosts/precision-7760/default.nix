{lib, ...}: {
  imports = [
    ../../global
    ../../features/desktop
    ../../features/system/nix-gl-host
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
}
