{inputs, ...}: (final: prev: let
  inherit (final) lib;
  nv =
    ((import ./.nvfetcher/generated.nix) {
      inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
    })
    .spectral;
  #   spectral-language-server = prev.spectral-language-server.override {
  #     inherit src;
  # # webpack --mode production --stats errors-warnings --config ./server/webpack.config.js
  #   };
  spectral = final.mkYarnPackage rec {
    inherit (nv) src pname version;

    nodejs = final.nodejs_22;
    yarn = final.yarn.override {inherit nodejs;};

    packageJSON = "${nv.src}/package.json";

    offlineCache = final.fetchYarnDeps {
      yarnLock = ./.nvfetcher/spectral/yarn.lock;
      # sha256 = "sha256-eD7Glb9L64iogc79P9ikcz8sYou83a+8LcJQgscfJ3U=";
      sha256 = lib.fakeSha256;
    };

    nativeBuildInputs = with final; [makeWrapper];

    preBuild = ''
    '';

    # popd
    # pushd deps/${nv.pname}
    buildPhase = ''
      runHook preBuild

      #yarn build
      ls -la
      ${lib.getExe yarn} workspace @stoplight/spectral-cli build.nix

      runHook postBuild
    '';

    postInstall = ''
      makeWrapper ${lib.getExe nodejs} "$out/bin/spectral" \
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
      homepage = "https://github.com/stoplightio/spectral";
      license = lib.licenses.asl20;
      maintainers = with lib.maintainers; [billiegoose];
    };
  };
in {
  inherit spectral;
})
