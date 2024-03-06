
{
  config,
  lib,
  pkgs,
  ...
}: {
  programs.starship = {
    package = pkgs.starship;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
    settings = {
      format = lib.concatStrings [
        "$status"
        "$username"
        "$hostname"
        "$directory"
        "$git_branch"
        "$git_state"
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
        style_user = "username";
        style_root = "error";
      };
      hostname = {
        format = "[@$hostname]($style) ";
        style = "hostname";
      };
      directory = {
        format = "[$read_only]($read_only_style)[$path]($style) ";
        repo_root_format = "[$read_only]($read_only_style)[$repo_root]($repo_root_style)[$path]($style) ";
        style = "directory";
        repo_root_style = "directory";
        read_only = " ";
        read_only_style = "error";
        truncation_symbol = "...";
      };
      character = {
        error_symbol = "[>](error)";
        success_symbol = "[>](success)";
        vimcmd_symbol = "[<](prompt0)";
        vimcmd_visual_symbol = "[<](prompt1)";
        vimcmd_replace_symbol = "[<](prompt2)";
        vimcmd_replace_one_symbol = "[<](prompt2)";
      };
      git_branch = {
        format = "[$symbol$branch(:$remote_branch)]($style) ";
        style = "git";
      };
      git_state = {
        style = "${config.colors.yellow}";
      };
      palette = "catppuccin-mocha";
      palettes.catppuccin-mocha = {
        error = config.colors.highlights.error.fg;
        success = config.colors.highlights.success.fg;
        prompt0 = config.colors.highlights.prompt0.fg;
        prompt1 = config.colors.highlights.prompt1.fg;
        prompt2 = config.colors.highlights.prompt2.fg;
        username = config.colors.highlights.username.fg;
        hostname = config.colors.highlights.hostname.fg;
        directory = config.colors.highlights.directory.fg;
        git = config.colors.highlights.git.fg;
      };
    };
  };
}
