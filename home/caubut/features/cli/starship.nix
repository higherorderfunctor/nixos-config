{
  config,
  lib,
  pkgs,
  ...
}: {
  programs.starship = {
    enable = true;
    package = pkgs.fzf;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    settings = {
      format = lib.concatStrings [
        "$status"
        "$username"
        "$hostname"
        "$directory"
        "$character"
      ];
      continuation_prompt = "▶▶ ";
      status = {
        format = "$symbol ";
        success_symbol = "[](success)";
        symbol = "[](error)";
        disabled = false;
      };
      username = {
        format = "[$user]($style)";
        style_user = config.colors.highlights.color12.fg;
        style_root = "error";
      };
      hostname = {
        format = "[@$hostname]($style) ";
        style = config.colors.highlights.color12.fg;
      };
      directory = {
        style = config.colors.highlights.color3.fg;
      };
      character = {
        error_symbol = "[>](error)";
        success_symbol = "[>](success)";
        vimcmd_symbol = "[<](yellow)";
        vimcmd_visual_symbol = "[<](cyan)";
        vimcmd_replace_symbol = "[<](purple)";
        vimcmd_replace_one_symbol = "[<](purple)";
      };
      palette = "catppuccin-mocha";
      palettes.catppuccin-mocha = {
        "error" = config.colors.highlights.error.fg;
        "success" = config.colors.highlights.success.fg;
      };
    };
  };
}
