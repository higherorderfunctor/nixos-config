{
  config,
  pkgs,
  ...
}: {
  home.packages = [pkgs.nvfetcher];
  sops.secrets = {
    "${config.home.username}-nvfetcher-keyfile" = {
      mode = "400";
    };
  };
}
