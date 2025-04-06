{
  config,
  inputs,
  ...
}: {
  imports = [
    inputs.nix-index-database.hmModules.nix-index
  ];
  programs.nix-index = {
    enable = true;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
  };
}
