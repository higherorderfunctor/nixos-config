{
  inputs,
  pkgs,
  ...
}: {
  programs.firefox = {
    enable = true;
    package = inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin;
  };
  home.packages = [
    (pkgs.linkFarm "firefox" [
      {
        name = "firefox";
        path = pkgs.firefox-nightly-bin;
      }
    ])
  ];
  # TODO: command-not-found db error
}
