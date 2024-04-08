{pkgs, ...}: {
  # home.sessionVariables = {
  #   LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib";
  # };
  home.packages = with pkgs; [
    gcc
    gccStdenv
    glibc
    libgcc.lib
    gdb
  ];
}
