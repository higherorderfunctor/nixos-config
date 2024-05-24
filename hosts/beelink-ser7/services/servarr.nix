{
  config,
  pkgs,
  ...
}: {
  # secrets
  sops.secrets = {
    "services.gluetun.wg0.config" = {
      mode = "400";
      sopsFile = ../secrets/servarr.yaml;
    };
    "services.gluetun.wg0" = {
      mode = "400";
      sopsFile = ../secrets/servarr.yaml;
    };
  };
  services.servarr = {
    enable = true;
    gluetun = {
      package = pkgs.gluetun;
      vpn = {
        protocol = "wireguard";
        portForwarding = {
          enabled = true;
          provider = "protonvpn";
        };
        endpoint.configFile = config.sops.secrets."services.gluetun.wg0.config".path;
      };
      # environmentFile = config.sops.secrets."servarr-gluetun.env".path;
      # wireguard = {
      #   config = config.sops.secrets."servarr-wg0.conf".path;
      # };
    };
  };
}
