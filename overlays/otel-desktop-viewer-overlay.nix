_: final: prev: let
  inherit (final) lib;
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    .otel-desktop-viewer;
  desktopexporter = final.buildGoModule rec {
    inherit (nv) pname src version;
    preBuild = ''
      set -x
      ls -la
      cd desktopexporter
    '';
    proxyVendor = true;
    allowGoReference = true;
    vendorHash = "sha256-xbnt7JqMePsHfyG3+5yjtouUjSTsbqHFR81e3PTaGzU=";
    # vendorHash = lib.fakeHash;
    postPatch = ''
      rm ./desktopexporter/internal/server/server_test.go \
          ./desktopexporter/internal/store/store_test.go
    '';
  };
  otel-desktop-viewer = final.buildGoModule rec {
    inherit (nv) pname src version;
    preBuild = ''
      set -x
      ls -la
      cd desktopcollector
    '';
    postInstall = ''
      ls -la
      ls -la $out
      mv $out/bin/desktopcollector $out/bin/otel-desktop-viewer
    '';
    # deleteVendor = true;
    proxyVendor = true;
    # buildInputs = [desktopexporter];
    allowGoReference = true;
    vendorHash = "sha256-7RKvY1KnoDTL4lL2dQBx7Mej48u76W46s7LZMyRrf2M=";
    # vendorHash = lib.fakeHash;
  };
in {
  inherit otel-desktop-viewer;
  # otel-desktop-viewer = final.stdenv.mkDerivation {
  #   # Dependencies
  #   buildInputs = [
  #     final.buildGoModule
  #     final.nodejs
  #     final.esbuild
  #     final.prettier
  #   ];

  #   # Build phases
  #   buildPhase = ''
  #     # Build Go binary
  #     cd desktopcollector
  #     go build -o ../otel-desktop-viewer

  #     # Build JavaScript/TypeScript
  #     cd ../desktopexporter/internal/app
  #     npm install
  #     npx esbuild --bundle main.tsx main.css --outdir=../server/static
  #   '';

  #   # Install phase
  #   installPhase = ''
  #     mkdir -p $out/bin
  #     cp ../otel-desktop-viewer $out/bin/
  #     cp -r ../desktopexporter/server/static $out/static
  #   '';

  #   meta = with final.lib; {
  #     description = "A CLI tool for receiving OpenTelemetry traces while working on your local machine that helps you visualize and explore your trace data without needing to send it on to a telemetry vendor.";
  #     license = licenses.apache2;
  #     maintainers = [maintainers.CtrlSpice];
  #   };
  # };
}
# .PHONY: install
# install:
# 	cd desktopexporter/internal/app; npm install
#
# .PHONY: build-go
# build-go:
# 	cd desktopcollector; go build -o ../otel-desktop-viewer
#
# .PHONY: test-go
# test-go:
# 	cd desktopexporter; go test ./...
#
# .PHONY: run-go
# run-go:
# 	SERVE_FROM_FS=true cd desktopcollector; go run ./...
#
# .PHONY: run-db-go
# run-db-go:
# 	SERVE_FROM_FS=true cd desktopcollector; go run ./... --db ../duck.db
#
# .PHONY: build-js
# build-js:
# 	cd desktopexporter/internal/app; npx esbuild --bundle main.tsx main.css --outdir=../server/static
#
# .PHONY: watch-js
# watch-js:
# 	cd desktopexporter/internal/app; npx esbuild --watch --bundle main.tsx main.css --outdir=../server/static
#
# .PHONY: format-js
# format-js:
# 	cd desktopexporter/internal/app; npx prettier -w app
#
# # esbuild will compile typescript files but will not typecheck them. This runs the
# # typescript typechecker but does not build the files.
# .PHONY: validate-typescript
# validate-typescript:
# 	cd desktopexporter/internal/app; npx tsc --noEmit
