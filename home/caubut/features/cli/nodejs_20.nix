{
  config,
  pkgs,
  ...
}: {
  home.packages = with pkgs; [
    nodejs_24
    yarn
    pnpm
  ];

  home.sessionVariables = {
    PNPM_HOME = "${config.xdg.dataHome}/pnpm";
  };
}
