{
  config,
  inputs,
  pkgs,
  outputs,
  ...
}: let
  username = "caubut";
in {
  imports =
    [
      inputs.impermanence.nixosModules.home-manager.impermanence
      ../features/cli
      ../features/colors/catppuccin-mocha.nix
    ]
    ++ (builtins.attrValues outputs.homeManagerModules);

  programs = {
    home-manager.enable = true;
    oh-my-posh.enable = true;
  };

  xdg = {
    enable = true;
    mime.enable = true;
    userDirs = {
      enable = true;
      createDirectories = true;
    };
  };

  services.nixos-config = {
    enable = true;
    path = "${config.xdg.userDirs.documents}/projects/nixos-config";
    remote = "git@github.com:higherorderfunctor/nixos-config.git";
  };

  systemd.user = {
    # switches services on rebuilds
    startServices = "sd-switch";
    # permission fixes
    tmpfiles.rules = [
      "z /home/${username}/.ssh 0700 ${username} ${username} - -"
      "z /persist/home/${username}/.ssh 0700 ${username} ${username} - -"
      "z /home/${username}/.local 0700 ${username} ${username} - -"
      "z /persist/home/${username}/.local 0700 ${username} ${username} - -"
      "z /home/${username}/.local/share 0700 ${username} ${username} - -"
      "z /persist/home/${username}/.local/share 0700 ${username} ${username} - -"
      "z /home/${username}/.local/state 0700 ${username} ${username} - -"
      "z /persist/home/${username}/.local/state 0700 ${username} ${username} - -"
    ];
  };

  home = {
    # TODO: temp?
    packages = [pkgs.cinnamon.nemo];
    # sessionVariables = {
    #   NIXOS_HOST = hostname;
    # };
    # pin state version
    inherit (import ../../../hosts/common/global/state-version.nix) stateVersion;
    inherit username;
    homeDirectory = "/home/${username}";
    persistence = {
      "/persist${config.home.homeDirectory}" = {
        directories = [
          "Documents"
          "Downloads"
          "Music"
          "Pictures"
          "Public"
          "Templates"
          "Videos"
        ];
        files = [
          ".ssh/known_hosts"
        ];
        allowOther = true;
      };
    };
  };
}
