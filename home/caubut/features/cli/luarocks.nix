{pkgs, ...}: {
  home.packages = [
    pkgs.luajitPackages.luarocks
  ];
}
