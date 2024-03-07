{lib, ...}: {
  imports = [
    ../../global
    ../../features/desktop
  ];
  # disable impermanence
  home.persistence = lib.mkForce {};
}
