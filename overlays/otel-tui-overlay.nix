_: final: _: let
  otel-tui =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    ."otel-tui-${final.system}";
in {
  otel-tui = final.stdenv.mkDerivation {
    name = "otel-tui";
    inherit (otel-tui) src version;

    phases = ["unpackPhase" "installPhase" "patchPhase"];

    unpackPhase = ''
      tar -xvf $src
    '';

    installPhase = ''
      ls -la
      mkdir -p $out/bin
      cp otel-tui $out/bin/otel-tui
      chmod +x $out/bin/otel-tui
    '';
  };
}
