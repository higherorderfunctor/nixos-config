{
  inputs,
  lib,
  config,
  ...
}: {
  imports = [
    inputs.impermanence.nixosModules.home-manager.impermanence
    ../features/cli
    # TODO: ../features/nvim
  ];

  systemd.user.startServices = "sd-switch";

  programs = {
    home-manager.enable = true;
  };

  home =
    # lock system and home-mnager state versions
    (import ../../../hosts/common/global/state-version.nix)
    // {
      username = lib.mkDefault "caubut";
      homeDirectory = lib.mkDefault "/home/${config.home.username}";

      persistence = {
        "/persist/home/caubut" = {
          directories = [
            "Documents"
            "Downloads"
            "Pictures"
            "Videos"
          ];
          allowOther = true;
        };
      };
    };
}
