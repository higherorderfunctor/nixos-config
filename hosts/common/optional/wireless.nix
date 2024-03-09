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
      "HOME_SSID_1" = {
        psk = "@HOME_PASS_1@";
      };
      "@HOME_SSID_2@" = {
        psk = "@HOME_PASS_2@";
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
