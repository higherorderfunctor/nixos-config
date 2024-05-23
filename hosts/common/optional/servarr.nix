{pkgs, ...}: {
  services.servarr = {
    enable = true;
    gluetun = {
      package = pkgs.gluetun;
    };
  };
}
