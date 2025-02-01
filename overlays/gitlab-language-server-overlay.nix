{lib, ...}: final: _: {
  gitlab-language-server = final.buildNpmPackage {
    pname = "gitlab-lsp";
    version = "7.10.0"; # Replace with a specific version if needed

    src = final.fetchFromGitLab {
      owner = "gitlab-org";
      repo = "editor-extensions/gitlab-lsp";
      rev = "v7.10.0"; # Replace with a specific commit or tag if needed
      sha256 = "sha256-FQYPVP1pDSKjPDcKVjv4qu/Q64E8WPGwYz+7vl315pQ="; # Replace with the actual hash
      # sha256 = lib.fakeHash; # Replace with the actual hash
    };

    buildInputs = [final.nodejs];

    # npmDepsHash = lib.fakeHash;
    npmDepsHash = "sha256-n0CzAIq3LaaGNO6wufodoJ7jStUhHknBRTjQ/J0GR3U=";
    npmBuild = "npm run build:language-server-only";
    forceGitDeps = true;
    makeCacheWritable = true;
    npmFlags = ["--legacy-peer-deps"];

    installPhase = ''
      mkdir -p $out/share/gitlab-language-server
      cp -r ./out/node/main-bundle.js $out/share/gitlab-language-server/main-bundle.js

      mkdir -p $out/bin
      makeWrapper ${lib.getExe final.nodejs} $out/bin/gitlab-language-server \
        --add-flags $out/share/gitlab-language-server/main-bundle.js
    '';

    meta = with final.lib; {
      description = "GitLab Language Server";
      homepage = "https://gitlab.com/gitlab-org/editor-extensions/gitlab-lsp";
      license = licenses.mit;
      maintainers = with maintainers; [];
    };
  };
}
