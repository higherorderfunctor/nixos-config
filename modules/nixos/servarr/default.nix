{lib, ...}: {
  imports = [
    ./vpn.nix
  ];
  options = {
    services.servarr.enable = lib.mkEnableOption "servarr";
  };
}
