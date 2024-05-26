{pkgs, ...}: {
  home.packages = (with pkgs.bind; [dnsutils host]) ++ (with pkgs; [knot-dns bridge-utils tcpdump]);
}
