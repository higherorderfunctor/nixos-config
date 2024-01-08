{
  config,
  lib,
  pkgs,
  ...
}: {
  programs.starship = {
    enable = true;
    package = pkgs.starship;
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
        vimcmd_symbol = "[<](prompt0)";
        vimcmd_visual_symbol = "[<](prompt1)";
        vimcmd_replace_symbol = "[<](prompt2)";
        vimcmd_replace_one_symbol = "[<](prompt2)";
      };
      palette = "catppuccin-mocha";
      palettes.catppuccin-mocha = {
        error = config.colors.highlights.error.fg;
        success = config.colors.highlights.success.fg;
        prompt0 = config.colors.prompt0.fg;
        prompt1 = config.colors.prompt1.fg;
        prompt2 = config.colors.prompt2.fg;
      };
    };
  };
}
