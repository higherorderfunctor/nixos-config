{pkgs, ...}: {
  home.packages = [pkgs.luajitPackages.luacheck];
}
