{
  config,
  inputs,
  pkgs,
  ...
}: let
  neovimWrapper = pkgs.symlinkJoin {
    name = "nvim";
    paths = [pkgs.neovim-nightly];
    buildInputs = [pkgs.makeWrapper];
    postBuild = "wrapProgram $out/bin/nvim --prefix PATH : $out/bin";
  };
in {
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    defaultEditor = true;
    extraPackages = with pkgs; [
      gcc
    ];
  };
  xdg.configFile = {
    nvim = {
      source = ./nvim-config;
      recursive = true;
    };
    "nvim/lazy-lock.json" = {
      source = config.lib.file.mkOutOfStoreSymlink "${config.xdg.configHome}/nvim/lazy-lock.json";
    };
  };
  home.activation = {
    nvim = inputs.home-manager.lib.hm.dag.entryAfter ["installPackages"] ''
      PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD nvim --headless "+Lazy! restore" +qa
    '';
  };
}
