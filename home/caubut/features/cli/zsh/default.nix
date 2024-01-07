{
  lib,
  pkgs,
  inputs,
  ...
}: {
  programs = {
    zsh = {
      enable = true;
      package = pkgs.zsh;
      # oh-my-zsh = {
      #   enable = true;
      #   plugins = ["git"];
      # };
    };
    fzf = {
      enable = true;
      package = pkgs.fzf;
      enableZshIntegration = true;
      colors = {
        # https://github.com/catppuccin/fzf
        "bg+" = "#313244";
        bg = "#1e1e2e";
        spinner = "#f5e0dc";
        hl = "#f38ba8";
        fg = "#cdd6f4";
        header = "#f38ba8";
        info = "#cba6f7";
        pointer = "#f5e0dc";
        marker = "#f5e0dc";
        "fg+" = "#cdd6f4";
        prompt = "#cba6f7";
        "hl+" = "#f38ba8";
      };
    };
    starship = {
      enable = true;
      settings = {
        format = ''
          $os
          $username
          $character
        '';
        character = {
          error_symbol = "[~~>](bold red)";
          success_symbol = "[->>](bold green)";
          vimcmd_symbol = "[<<-](bold yellow)";
          vimcmd_visual_symbol = "[<<-](bold cyan)";
          vimcmd_replace_symbol = "[<<-](bold purple)";
          vimcmd_replace_one_symbol = "[<<-](bold purple)";
        };
      };
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
