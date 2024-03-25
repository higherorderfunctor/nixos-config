{inputs, ...}: (final: _: let
  inherit (final) lib;
  nv = (import ./nvpkgs.nix).spectral;
  src = final.fetchFromGitHub {
    inherit (nv.src) owner repo rev sha256;
  };
  spectral = final.mkYarnPackage {
    inherit (nv) version;
    inherit src;
    pname = nv.name;

    packageJSON = "${src}/package.json";

    offlineCache = final.fetchYarnDeps {
      yarnLock = "${src}/yarn.lock";
      sha256 = lib.fakeSha256;
    };

    nativeBuildInputs = [final.makeWrapper];

    preBuild = ''

    '';

    buildPhase = ''
      runHook preBuild

      pushd deps/${nv.name}
      yarn run build
      popd

      runHook postBuild
    '';

    postInstall = ''
      makeWrapper ${final.nodejs}/bin/node "$out/bin/spectral" \
        --add-flags "$out/libexec/spectral/deps/spectral/lib/index.js"
    '';

    passthru = {
      tests = {
      };
    };

    # The prepack script runs the build script, which we'd rather do in the build phase.
    # npmPackFlags = ["--ignore-scripts"];

    # NODE_OPTIONS = "--openssl-legacy-provider";

    meta = {
      #description = builtins.foldl' (acc: part: acc + part) "" [
      #  "A flexible JSON/YAML linter for creating automated "
      #  "style guides, with baked in support for OpenAPI "
      #  "v3.1, v3.0, and v2.0 as well as AsyncAPI v2.x."
      #];
      homepage = "https://github.com/stoplightio/spectral";
      license = lib.licenses.asl20;
      maintainers = with lib.maintainers; [billiegoose];
    };
  };
in {
  # inherit spectral;
})
