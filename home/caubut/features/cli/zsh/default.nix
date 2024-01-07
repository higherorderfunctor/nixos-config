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
        format = lib.concatStrings [
          "\${custom.os-on-error}\${custom.os-on-success} "
          "$username"
          "$character"
        ];
        custom = {
          os-on-error = {
            format = "[]($style)";
            style = "bold red";
            when = "test $status -ne 0";
          };
          os-on-success = {
            format = "($style)";
            style = "bold green";
            when = "test $status -eq 0";
          };
        };
        continuation_prompt = "▶▶ ";
        character = {
          error_symbol = "[~~>](bold red)";
          success_symbol = "[->>](bold green)";
          vimcmd_symbol = "[<<-](bold yellow)";
          vimcmd_visual_symbol = "[<<-](bold cyan)";
          vimcmd_replace_symbol = "[<<-](bold purple)";
          vimcmd_replace_one_symbol = "[<<-](bold purple)";
        };
        palette = "catppuccin-mocha";
        palettes.catppuccin-mocha = {
          "blue" = "#89B4FA";
          "green" = "#a6e3a1";
          "lavender" = "#B4BEFE";
          "os" = "#ACB0BE";
          "pink" = "#F5C2E7";
          "red" = "#f38ba8";
        };
      };
    };
    # continuation_prompt = "▶▶ "
    # format = "$status$username$hostname$directory$character"
    #
    # [status]
    # format = "$symbol "
    # success_symbol = "[](green)"
    # symbol = "[](red)"
    # style = "os"
    # disabled = false
    #
    # [username]
    # style_user = "blue"
    # style_root = "red"
    # format = "[$user]($style)"
    #
    # [hostname]
    # format = '[@$hostname]($style) '
    # style = "blue"
    #
    # [character]
    # error_symbol = "[~~>](bold red)"
    # success_symbol = "[->>](bold green)"
    # vimcmd_replace_one_symbol = "[<<-](bold purple)"
    # vimcmd_replace_symbol = "[<<-](bold purple)"
    # vimcmd_symbol = "[<<-](bold yellow)"
    # vimcmd_visual_symbol = "[<<-](bold cyan)"
    #
    # [palettes.catppuccin-mocha]
    # blue = "#89B4FA"
    # green = "#a6e3a1"
    # lavender = "#B4BEFE"
    # os = "#ACB0BE"
    # pink = "#F5C2E7"
    # red = "#f38ba8"

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
