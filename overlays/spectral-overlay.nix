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
  spectral2 = let
    yarnLock = "${final.stdenvNoCC.mkDerivation {
      pname = "spectral-yarn-lock";
      inherit (nv) version;
      nativeBuildInputs = with final; [yarn];
      phases = ["buildPhase"];
      buildPhase = ''
        ${lib.getExe final.yarn-lock-converter} -i ${nv.src}/yarn.lock -o $out/yarn.lock
      '';
    }}/yarn.lock";
  in
    final.mkYarnPackage {
      inherit (nv) src pname version;

      nodejs = final.nodejs_22;
      packageJSON = "${nv.src}/package.json";

      offlineCache = final.fetchYarnDeps {
        inherit yarnLock;
        sha256 = lib.fakeSha256;
      };

      nativeBuildInputs = with final; [makeWrapper nodejs_22];

      preBuild = ''
      '';

      # popd
      # pushd deps/${nv.pname}
      buildPhase = ''
        runHook preBuild

        #yarn build
        ls -la
        ${lib.getExe final.yarn} workspace @stoplight/spectral-cli build.nix

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
        homepage = "https://github.com/stoplightio/spectral";
        license = lib.licenses.asl20;
        maintainers = with lib.maintainers; [billiegoose];
      };
    };
in {
  inherit spectral2;
})
