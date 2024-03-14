{pkgs, ...}: let
  rustPlatform = pkgs.makeRustPlatform {
    cargo = pkgs.rust-bin.stable.latest.default;
    rustc = pkgs.rust-bin.stable.latest.default;
  };
  pname = "fblog";
  version = "4.8.0";
  src = pkgs.fetchFromGitHub {
    owner = "brocode";
    repo = pname;
    rev = "v${version}";
    hash = "sha256-T0NvcNg2UeUpEf1hjSdoaUkIzCAP29vo6edfeno/oyo=";
  };
  cargoHash = "sha256-n7m4YShWtjoF+vrzgiJX1chT4RSOozvwq+RRO7r6uxI=";
  fblog =
    pkgs.fblog.override
    (_: {
      rustPlatform.buildRustPackage = args:
        rustPlatform.buildRustPackage (args
          // {
            inherit pname version src cargoHash;
          });
    });
in {
  home.packages = [fblog];
}
