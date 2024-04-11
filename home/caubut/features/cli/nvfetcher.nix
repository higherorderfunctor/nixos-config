{
  config,
  pkgs,
  ...
}: {
  home.packages = [pkgs.nvfetcher];
  sops.secrets = {
    "${config.home.username}-nvfetcher-keyfile" = {
      path = "${config.xdg.configHome}/nvfetcher/keyfile.toml";
      mode = "400";
    };
  };
}
