{pkgs, ...}: {
  # home.sessionVariables = {
  #   LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib";
  # };
  home.packages = [
    pkgs.gcc
    pkgs.gccStdenv
    pkgs.glibc
    pkgs.libgcc.lib
  ];
}
