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
        name = "bin/firefox";
        path = "${inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin}/bin/firefox-nightly";
      }
    ])
  ];
  # TODO: command-not-found db error
}
