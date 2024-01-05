{
  config,
  inputs,
  lib,
  ...
}: {
  imports = [
    inputs.impermanence.nixosModules.home-manager.impermanence
    ../features/cli
    ../features/neovim
  ];

  # TODO: not needed with global pkgs
  # nixpkgs = {
  #   overlays = [
  #     inputs.neovim-nightly-overlay.overlay
  #   ];
  #   config = {
  #     allowUnfree = true;
  #   };
  # };

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
      file."Documents.personal.nixos-config" = {
        source = inputs.self.outPath;
        recursive = true;
      };
    };
}
