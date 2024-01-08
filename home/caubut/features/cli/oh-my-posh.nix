{
  config,
  pkgs,
  ...
}: {
  programs.oh-my-posh = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    package = let
      version = "19.4.0";
      src = pkgs.fetchFromGitHub {
        owner = "jandedobbeleer";
        repo = "oh-my-posh";
        rev = "refs/tags/v${version}";
        # hash = lib.fakeSha256;
        hash = "sha256-e3KYqCLbnjDKO4tiL/BssUmxmmsWJFqA1gOvwF9r7jo=";
      };
    in
      pkgs.oh-my-posh.override (_: {
        inherit version src;
        buildGoModule = args:
          pkgs.buildGoModule (args
            // {
              inherit version src;
              # vendorHash = lib.fakeSha256;
              vendorHash = "sha256-//L0tjM+JELglwCOWkifn39G4JuL/YBmJKBF1Uyno3M=";
              postPatch = ''
                # these tests requires internet access
                rm engine/image_test.go \
                  engine/migrate_glyphs_test.go \
                  segments/nba_test.go
              '';
            });
      });
    settings =
      builtins.fromJSON
      (builtins.unsafeDiscardStringContext
        (builtins.readFile ./catppuccin.omp.json));
    #   settings = {
    #     "$schema" = "https://raw.githubusercontent.com/JanDeDobbeleer/oh-my-posh/main/themes/schema.json";
    #     version = 2;
    #     final_space = true;
    #     "blocks" = [
    #       {
    #         "type" = "prompt";
    #         "alignment" = "left";
    #         "segments" = [
    #           {
    #             "type" = "os";
    #             "style" = "plain";
    #             "foreground" = "p:os";
    #             "foreground_templates" = [
    #               "{{ if eq .Code 0 }}p=green{{ else }}p:red{{ end }}"
    #             ];
    #             "template" = "{{ .Icon }} ";
    #           }
    #           {
    #             "type" = "session";
    #             "style" = "plain";
    #             "foreground" = "p:blue";
    #             "template" = "{{ .UserName }}@{{ .HostName }} ";
    #           }
    #           {
    #             "type" = "path";
    #             "style" = "plain";
    #             "foreground" = "p:pink";
    #             "template" = "{{ .Path }} ";
    #             "properties" = {
    #               "folder_icon" = "....";
    #               "home_icon" = "~";
    #               "style" = "agnoster_short";
    #             };
    #           }
    #           {
    #             "type" = "git";
    #             "style" = "plain";
    #             "foreground" = "p:lavender";
    #             "template" = "{{ .HEAD }} ";
    #             "properties" = {
    #               "branch_icon" = " ";
    #               "cherry_pick_icon" = " ";
    #               "commit_icon" = " ";
    #               "fetch_status" = false;
    #               "fetch_upstream_icon" = false;
    #               "merge_icon" = "} ";
    #               "no_commits_icon" = " ";
    #               "rebase_icon" = " ";
    #               "revert_icon" = " ";
    #               "tag_icon" = " ";
    #             };
    #           }
    #           {
    #             "type" = "text";
    #             "style" = "plain";
    #             "foreground" = "p:closer";
    #             "template" = "";
    #           }
    #         ];
    #       }
    #     ];
    #     "palette" = {
    #       "blue" = "#89B4FA";
    #       "closer" = "p:os";
    #       "green" = "#a6e3a1";
    #       "lavender" = "#B4BEFE";
    #       "os" = "#ACB0BE";
    #       "pink" = "#F5C2E7";
    #       "red" = "#f38ba8";
    #     };
    #   };
  };
}
