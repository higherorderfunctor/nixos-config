{lib, ...}: final: _: let
  nv = (import ./nvpkgs.nix).gitlab-language-server;
in {
  gitlab-language-server = final.buildNpmPackage {
    pname = "gitlab-language-server";
    inherit (nv) version npmDepsHash;

    src = final.fetchgit {
      inherit
        (nv.src)
        url
        rev
        fetchSubmodules
        deepClone
        leaveDotGit
        sparseCheckout
        sha256
        ;
    };

    patches = [./.nvfetcher/gitlab-language-server/fix-package-lock.patch];

    buildInputs = [final.nodejs];

    # npmDepsHash = "sha256-n0CzAIq3LaaGNO6wufodoJ7jStUhHknBRTjQ/J0GR3U=";
    npmBuild = "npm run build:language-server-only";
    forceGitDeps = true;
    npmFlags = ["--legacy-peer-deps"];
    makeCacheWritable = true;

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
