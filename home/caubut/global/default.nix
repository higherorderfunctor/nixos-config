{
  config,
  inputs,
  outputs,
  pkgs,
  ...
}: let
  username = "caubut";

  toml = pkgs.formats.toml {};
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
    direnv = {
      enable = true;
      enableBashIntegration = config.programs.bash.enable;
      enableZshIntegration = config.programs.zsh.enable;
      nix-direnv.enable = true;
    };
  };

  xdg.configFile."direnv/direnv.toml".source = toml.generate "direnv.toml" {
    global = {
      hide_env_diff = true;
    };
    whitelist = {
      prefix = ["${config.xdg.userDirs.documents}/projects" "${config.xdg.userDirs.documents}/work"];
    };
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
    packages = with pkgs; [cinnamon.nemo dive];
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
        allowOther = true;
      };
    };
  };
}
