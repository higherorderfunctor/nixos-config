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
  # TODO tree sitter just needs gcc, remove extra package
  # TODO: tree sitter no vector
  programs.neovim = {
    enable = true;
    package = pkgs.neovim-nightly;
    defaultEditor = true;
    extraPackages = with pkgs; [
      cargo
      clang
      clangStdenv
      alejandra
      beautysh
      cmake
      fd
      deadnix
      fish
      gnumake
      lazygit
      luajit
      luajitPackages.luarocks
      nodejs_21
      ripgrep
      sqlite
      unzip
      # tree-sitter
      wget
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
