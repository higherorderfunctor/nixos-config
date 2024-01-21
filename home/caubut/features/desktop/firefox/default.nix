{
  inputs,
  pkgs,
  ...
}: {
  programs.firefox = {
    enable = true;
    # use nightly package
    package = inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin;
  };
  # alias 'firefox-nightly' to 'firefox'
  home.packages = [
    (pkgs.linkFarm "firefox" [
      {
        name = "bin/firefox";
        path = "${inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin}/bin/firefox-nightly";
      }
    ])
  ];
  # TODO: command-not-found db error
}
