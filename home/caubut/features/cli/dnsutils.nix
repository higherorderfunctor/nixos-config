{pkgs, ...}: {
  home.packages = with pkgs.bind; [dnsutils host];
}
