{
  config,
  pkgs,
  ...
}: {
  sops.secrets = {
    "servarr-wireguard-config" = {
      mode = "400";
      sopsFile = ../secrets/servarr.yaml;
    };
  };
  services.servarr = {
    enable = true;
    gluetun = {
      package = pkgs.gluetun;
      settings = {
        vpn = {
          provider = "custom";
          protocol = "wireguard";
          portForwarding = {
            enabled = true;
            provider = "protonvpn";
          };
          endpoint.configFile = config.sops.secrets."servarr-wireguard-config".path;
        };
      };
    };
  };
}
