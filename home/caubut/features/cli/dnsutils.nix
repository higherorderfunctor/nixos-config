{pkgs, ...}: {
  home.packages = (with pkgs.bind; [dnsutils host]) ++ (with pkgs; [bridge-utils tcpdump]);
}
