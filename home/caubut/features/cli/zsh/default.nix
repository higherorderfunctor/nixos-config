{
  config,
  lib,
  pkgs,
  ...
}: {
  programs = {
    zsh = {
      enable = true;
      package = pkgs.zsh;
      defaultKeymap = "viins";
      history = {
        path = "${config.xdg.dataHome}/zsh/zsh_history";
      };
      # oh-my-zsh = {
      #   enable = true;
      #   plugins = ["git"];
      # };
    };
    # oh-my-posh = {
    #   enable = true;
    #   package = let
    #     version = "19.4.0";
    #     src = pkgs.fetchFromGitHub {
    #       owner = "jandedobbeleer";
    #       repo = "oh-my-posh";
    #       rev = "refs/tags/v${version}";
    #       # hash = lib.fakeSha256;
    #       hash = "sha256-e3KYqCLbnjDKO4tiL/BssUmxmmsWJFqA1gOvwF9r7jo=";
    #     };
    #   in
    #     pkgs.oh-my-posh.override (prev: {
    #       buildGoModule = args:
    #         pkgs.buildGoModule (args
    #           // {
    #             inherit version src;
    #             # vendorHash = lib.fakeSha256;
    #             vendorHash = "sha256-//L0tjM+JELglwCOWkifn39G4JuL/YBmJKBF1Uyno3M=";
    #             postPatch = ''
    #               # these tests requires internet access
    #               rm engine/image_test.go \
    #                 engine/migrate_glyphs_test.go \
    #                 segments/nba_test.go
    #             '';
    #           });
    #     });
    #   settings =
    #     builtins.fromJSON
    #     (builtins.unsafeDiscardStringContext
    #       (builtins.readFile ./catppuccin.omp.json));
    # };
  };
}
