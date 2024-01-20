{
  inputs,
  pkgs,
  ...
}: {
  programs.firefox = {
    enable = true;
    package = pkgs.linkFarm "firefox" [
      {
        name = "firefox";
        path = inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin;
      }
    ];
  };
  # TODO: command-not-found db error
  #
  # why 115?
  # $ ls /nix/store | grep firefox
  # 0fnac0rwpwsszk5lps2sivih92bq6z5a-firefox-nightly-bin-unwrapped-123.0a1.drv
  # 3jharsfzy601i06r8mgidvrz35zcany1-firefox-nightly-bin-123.0a1
  # 6gh5psvs357yy0jm226fxlylh5zgbqib-firefox-123.0a1.en-US.linux-x86_64.tar.bz2.asc.drv
  # 8hfdv3m78d6kidkqbcfp5h8sg4sy1awy-firefox-nightly.desktop.drv
  # 9smrqyirdjrrfsf77g6dysjb48d6jxy4-firefox-policies.json.drv
  # b9dj1zsn4cdajwn1nbfssllliz097qc4-firefox-115.2.0esr.source.tar.xz.drv
  # d0ridjrmbkapckccwf8yd2yzg64wjgy4-firefox-syncserver.md
  # f668zvhjkf5pgnl5n8l6aqljahjihni2-firefox-nightly-bin-123.0a1.drv
  # g09p9i6gk5ad5hs0jrjqx6g2kqpyccpi-firefox-policies.json
  # k1gixds21aiqj16bxi64ivl4j59j68cm-firefox-nightly-bin-unwrapped-123.0a1
  # kzynfsgjdcc7ic10xxp4yyb4w7iyrmph-firefox-123.0a1.en-US.linux-x86_64.tar.bz2.drv
}
