{config, ...}: {
  sops.secrets = {
    "servarr-vpn-private-key" = {
      mode = "400";
      sopsFile = ../secrets/servarr.yaml;
    };
  };

  # networking.nat = {
  #   enable = true;
  #   internalInterfaces = ["ve-+"];
  #   externalInterface = "enp1s0";
  # };

  services.servarr = {
    enable = true;
    vpn = {
      endpoint.address = "149.50.216.205";
      address = ["10.2.0.2/32"];
      publicKey = "HVtWzUJa32VYzRy4EW30N0qwrJVNUzdbrX40r2hwHgY=";
      privateKeyFile = config.sops.secrets."servarr-vpn-private-key".path;
    };
  };
}
