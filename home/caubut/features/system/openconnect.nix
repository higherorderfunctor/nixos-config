{pkgs, ...}: {
  home.packages = with pkgs; [
    openconnect_openssl
    oath-toolkit
    vpn-slice
  ];
}
