{
  lib,
  pkgs,
  ...
}: {
  programs = {
    zsh = {
      enable = true;
      package = pkgs.zsh;
      oh-my-zsh = {
        enable = true;
        plugins = ["git"];
      };
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
    oh-my-posh = {
      enable = true;
      package = pkgs.oh-my-posh.overrideAttrs (_: prev: let
        version = "19.4.0";
        name = "oh-my-posh";
        src = pkgs.fetchFromGitHub {
          owner = "jandedobbeleer";
          repo = "oh-my-posh";
          rev = "refs/tags/v${version}";
          # hash = lib.fakeSha256;
          hash = "sha256-e3KYqCLbnjDKO4tiL/BssUmxmmsWJFqA1gOvwF9r7jo=";
        };
        # TODO: append
        postPatch = ''
          # these tests requires internet access
          rm engine/image_test.go \
            engine/migrate_glyphs_test.go \
            segments/nba_test.go
        '';
      in {
        inherit version name src postPatch;
        go-modules =
          (pkgs.buildGoModule {
            inherit version name src postPatch;
            vendorHash = null;
            vendorSha256 = lib.fakeSha256;
          })
          .go-modules;
      });
      settings =
        builtins.fromJSON
        (builtins.unsafeDiscardStringContext
          (builtins.readFile ./catppuccin.omp.json));
    };
  };
}
