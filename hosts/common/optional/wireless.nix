{config, ...}: {
  sops.secrets.wireless = {
    sopsFile = ../secrets/wireless.yaml;
  };

  networking.wireless = {
    enable = true;

    # prevent downgrade attacks
    fallbackToWPA2 = false;

    # declarative configuration
    environmentFile = config.sops.secrets.wireless.path;
    networks = {
      "WiFi 6e TEST Please Ignore" = {
        psk = "@HOME_PASS@";
      };
      "Another TEST Please Ignore" = {
        psk = "@HOME_PASS@";
      };
    };

    # allow users to override declarative configuration
    allowAuxiliaryImperativeNetworks = true;
    userControlled = {
      enable = true;
      group = "network";
    };
    extraConfig = ''
      update_config=1
    '';
  };

  # creates user group if nonexistent
  users.groups.network = {};

  # creates file if nonexistent
  systemd.services.wpa_supplicant.preStart = "touch /etc/wpa_supplicant.conf";
}
