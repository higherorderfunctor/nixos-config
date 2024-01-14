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
  xdg.configFile.nvim.source =
    config.lib.file.mkOutOfStoreSymlink
    "${config.xdg.userDirs.documents}/projects/nixos-config/home/${config.home.username}/features/neovim/nvim-config";
  # home.activation = {
  #   nvim = inputs.home-manager.lib.hm.dag.entryAfter ["installPackages"] ''
  #     ### cp ${config.xdg.configFile.nvim.source}/../lazy-lock.json ${config.xdg.configHome}/nvim/
  #     PATH="${config.home.path}/bin:$PATH" $DRY_RUN_CMD nvim --headless "+Lazy! restore" +qa
  #   '';
  # };
}
