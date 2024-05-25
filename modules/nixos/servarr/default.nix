{lib, ...}: {
  imports = [
    ./vpn.nix
  ];
  # machinectl list
  options = {
    services.servarr.enable = lib.mkEnableOption "servarr";
  };

  # config = lib.mkMerge [
  #   vpn.config
  # ];
}
