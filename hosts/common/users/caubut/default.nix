{
  config,
  pkgs,
  ...
}: let
  username = "caubut";
  ifGroupExist = groups: builtins.filter (group: builtins.hasAttr group config.users.groups) groups;
in {
  users.groups.${username} = {
    gid = 1000;
  };

  # TODO: services.gnome.gnome-keyring.enable
  services.gnome = {
    gnome-keyring.enable = true;
    gnome-settings-daemon.enable = true;
  };
  security = {
    polkit.enable = true;
    pam.services.ags = {};
  };
  # packages = [pkgs.gnomeExtensions.advanced-volume-control];
  environment.systemPackages = with pkgs;
  with gnome; [
    #gnome.adwaita-icon-theme
    #loupe
    #adwaita-icon-theme
    #nautilus
    #baobab
    gnome-calendar
    gnome-boxes
    gnome-system-monitor
    gnome-control-center
    gnome-weather
    gnome-calculator
    gnome-clocks
    gnome-software # for flatpak
    # wl-gammactl
    wl-clipboard
    gnome-settings-daemon
    # wayshot
    # pavucontrol
    # brightnessctl
    # swww
  ];
  # services.xserver = {
  #   # displayManager.gdm.enable = true;
  #   desktopManager.gnome = {
  #     enable = true;
  #     # extraGSettingsOverridePackages = [
  #     #   pkgs.nautilus-open-any-terminal
  #     # ];
  #   };
  # };
  services.udev.packages = with pkgs; [gnome.gnome-settings-daemon];

  users.users.${username} = {
    uid = 1000;
    group = "${username}";
    isNormalUser = true;
    shell = pkgs.zsh;
    extraGroups =
      [
        "wheel"
        "video"
        "audio"
      ]
      ++ ifGroupExist [
        "network"
      ];
    hashedPasswordFile = config.sops.secrets."${username}-password".path;
    packages = [pkgs.home-manager];
  };

  environment.etc = {
    "ssh/authorized_keys.d/${username}" = {
      text = pkgs.lib.mkDefault (
        pkgs.lib.mkAfter (
          builtins.readFile ../../../../home/${username}/secrets/personal_ed25519_key.pub
        )
      );
      mode = "0444";
    };
  };

  # TODO: ssh agent error in journal
  # TODO passwordless sudo not working

  # defines at system level since there is no
  # key for home manager to unlock secrets
  sops.secrets = {
    "${username}-personal-ed25519-key" = {
      owner = "${username}";
      mode = "400";
      sopsFile = ../../../../home/${username}/secrets/secrets.yaml;
    };
    "${username}-password" = {
      neededForUsers = true;
      sopsFile = ../../../../home/${username}/secrets/secrets.yaml;
    };
  };

  # host specific home-manager configuration for user
  home-manager.users.caubut = import ../../../../home/${username}/hosts/${config.networking.hostName};
}
